
namespace WebBuiltin {

static const char apiJs[] PROGMEM =
R"==(
const API = {
    to2(it) {
        if (it < 10) {
            return `0${it}`
        }
        return `${it}`
    },
    async setMode(mode) {
        return await fetch(`/api/mode${mode ? 1 : 0}`)
    },
    async addTime(time) {
        const url = `/api/on/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url)
    },
    async removeTime(time) {
        const url = `/api/remove/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url)
    },
    async setEvery(time) {
        const url = `/api/every/${to2(time.start.hour)}${to2(time.start.minute)}/for/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url)
    },

}
)==";


static const char appCss[] PROGMEM =
R"==(
:root {
  font-family: Inter, system-ui, Avenir, Helvetica, Arial, sans-serif;
  line-height: 1.5;
  font-weight: 400;

  color-scheme: light dark;

  --bg: #f5f5f5;
  --surface: #ffffff;
  --line: #0000001a;
  --field: #0000000c;
  --text: #000000;
}

@media (prefers-color-scheme: dark) {
  :root {
    --text: #b5b5b5;
    --bg: #101010;
    --surface: #000000;
    --line: #ffffff20;
    --field: #ffffff0c;
  }

  h1,
  h2,
  h3 {
    color: #ffffff;
  }

  #rail span.active {
    background-color: #ffffff20 !important;
  }

  svg {
    filter: invert();
  }
}

body {
  background-color: var(--bg);
  padding: 0 12px;
  color: var(--text);
}

* {
  margin: 0;
  padding: 0;
}

header {
  position: sticky;
  margin: 0 -12px;
  padding: 8px 8px 8px 16px;
  top: 0;
  background-color: var(--surface);
  border-bottom: 1px solid var(--line);
  display: flex;
  justify-content: space-between;
  align-items: center;
}

main {
  margin: 12px auto;
  max-width: 320px;
  padding: 12px;
  border-radius: 6px;
  background-color: var(--surface);
  border: 1px solid var(--line);
}

.mode {
  display: flex;
  justify-content: space-between;
}

input {
  border: none;
  background-color: var(--field);
  padding: 8px;
  border: 1px solid var(--line);
  border-radius: 8px;
}

input:focus {
  outline: 3px solid rgba(34, 73, 247, 0.379);
  outline-offset: 2px;
}

h3 {
  font-size: 1rem;
  margin: 0 0 12px 0;
}

#swap-mode label {
  margin: 0 10px;
}

#time-mode label {
  margin: 0 4px 0 10px;
}

#time-mode label:first-child {
  margin-left: 0;
}

#rail {
  background-color: var(--field);
  padding: 2px 4px;
  display: flex;
  border-radius: 16px;
  border: 1px solid var(--line);
  transition: all .3s;
}

#rail:active {
  background-color: var(--line);
}

#rail span {
  display: block;
  width: fit-content;
  opacity: .5;
  background: none;
  line-height: 1;
  padding: 8px;
  margin: 2px;
  transition: all .2s;
  border-radius: 18px;
  box-shadow: 0px 0px 0px rgba(0, 0, 0, 0);
}


#rail span.active {
  opacity: 1;
  background-color: #ffffff;
  border-radius: 12px;
  box-shadow: 0px 2px 12px rgba(0, 0, 0, 0.12);
  /* font-weight: 500; */
}

.icon {
  display: block;
  padding: 8px 6px 4px 6px;
  /* padding: auto; */
  border: none;
  background: none;
  border-radius: 8px;
}

.inputWrapper {
  display: flex;
  align-items: center;
  gap: 6px;
}

.inputWrapper .icon {
  margin-left: 2px;
}

.inputWrapper {
  padding: 12px 0;
}

.inputWrapper:not(:first-child) {
  border-top: 1px solid var(--line);
}

.add {
  /* opacity: .76; */
  width: 100%;
  margin-top: 12px;
  height: 2rem;
  background-color: var(--field);
  border: 1px dashed var(--line);
}

button:active {
  transition: all .3s;
}

button:active {
  background-color: var(--line);
}

.notfound {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100vh;
}

.notfound div p {
  opacity: .65;
}

#mode-selector {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

#swap-mode div:not(:last-child) {
  margin-bottom: 12px;
}
)==";


static const char indexHtml[] PROGMEM =
R"==(
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8" />
  <link rel="stylesheet" href="app.css">
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <script src="api.js" defer></script>
  <script src="main.1.js" defer></script>
  <script src="main.2.js" defer></script>
  <title>ตั้งค่า</title>
</head>

<body>
  <header>
    <h2> ตั้งค่า </h2>
  </header>

  <main id="systeminfo">
    <h3> ข้อมูลระบบ </h3>
    <p> เวลาระบบ |systemTime| </p>
  </main>
  
  <main id="mode-selector">
    <p> เลือกโหมด </p>
    <div id="rail">
      <span onclick="mode = true; update()"> ตั้งเวลา </span>
      <span onclick="mode = false; update()" class="active"> สลับ </span>
    </div>
  </main>

  <main id="swap-mode">
    <div>
    <h3> เปืดเครื่องสูบน้ำทุกๆ </h3>
      <input id="s1" name="ehour" type="number" value=|everyHour| min="0" max="24">
      <label for="ehour"> ชั่วโมง </label>
      <input id="s2" name="eminute" type="number" value=|everyMinute| min="0" max="60">
      <label for="eminute"> นาที </label>
    </div>
    <div>
      <h3> เป็นเวลา </h3>
      <input id="s3" name="fhour" type="number" value=|forHour| min="0" max="24">
      <label for="fhour"> ชั่วโมง </label>
      <input id="s4" name="fminute" type="number" value=|forMinute| min="0" max="60">
      <label for="fminute"> นาที </label>
    </div>
  </main>

  <main id="time-mode">
    <h3> กำหนดช่วงเวลา </h3>

    <div id="list">
      <!-- <div class="inputWrapper">
        <label for="hour"> เริ่ม </label>
        <input id="s3" name="hour" type="time" value="12:30">
        <label for="hour"> ถึง </label>
        <input id="s4" name="minute" type="time">
        <button class="icon">
          <svg xmlns="http://www.w3.org/2000/svg" height="18" viewBox="0 96 960 960" width="18">
            <path
              d="M261 936q-24 0-42-18t-18-42V306h-11q-12.75 0-21.375-8.675-8.625-8.676-8.625-21.5 0-12.825 8.625-21.325T190 246h158q0-13 8.625-21.5T378 216h204q12.75 0 21.375 8.625T612 246h158q12.75 0 21.375 8.675 8.625 8.676 8.625 21.5 0 12.825-8.625 21.325T770 306h-11v570q0 24-18 42t-42 18H261Zm0-630v570h438V306H261Zm106 454q0 12.75 8.675 21.375 8.676 8.625 21.5 8.625 12.825 0 21.325-8.625T427 760V421q0-12.75-8.675-21.375-8.676-8.625-21.5-8.625-12.825 0-21.325 8.625T367 421v339Zm166 0q0 12.75 8.675 21.375 8.676 8.625 21.5 8.625 12.825 0 21.325-8.625T593 760V421q0-12.75-8.675-21.375-8.676-8.625-21.5-8.625-12.825 0-21.325 8.625T533 421v339ZM261 306v570-570Z" />
          </svg>
        </button>
      </div> -->
    </div>

    <button class="icon add" onclick="addTimeItem()">
      <svg xmlns="http://www.w3.org/2000/svg" height="18" viewBox="0 96 960 960" width="18">
        <path
          d="M479.825 856Q467 856 458.5 847.375T450 826V606H230q-12.75 0-21.375-8.675-8.625-8.676-8.625-21.5 0-12.825 8.625-21.325T230 546h220V326q0-12.75 8.675-21.375 8.676-8.625 21.5-8.625 12.825 0 21.325 8.625T510 326v220h220q12.75 0 21.375 8.675 8.625 8.676 8.625 21.5 0 12.825-8.625 21.325T730 606H510v220q0 12.75-8.675 21.375-8.676 8.625-21.5 8.625Z" />
      </svg>
    </button>

  </main>

</body>
</html>
)==";


static const char main1[] PROGMEM =
R"==(
const $ = (id) => document.getElementById(id)

const rail = $('rail')
const swapDisplay = $('swap-mode')
const timeDisplay = $('time-mode')
const timeListDisplay = $('list')

// let mode = |mode|
let mode = true

const swapConfig = {
    every: {
        hour: 2,
        minute: 30
    },
    for: {
        hour: 1,
        minute: 15
    }
}

const timeList = [
    {
        start: {
            hour: 10,
            minute: 0
        },
        end: {
            hour: 11,
            minute: 30,
        }
    },
    {
        start: {
            hour: 13,
            minute: 0
        },
        end: {
            hour: 14,
            minute: 30
        }
    }
]

const to2 = it => {
    if (it === undefined) {
        return '00'
    }
    if (it < 10) {
        return `0${it}`
    }
    return `${it}`
}

const inputListeners = [] // { id: number, listener: EventListener, for: HTMLInputElement }

const timeItemTemplate = (id, time) => `
  <div class="inputWrapper">
    <label for="start${id}"> เริ่ม </label>
    <input id="ts${id}" name="start${id}" type="time" value="${to2(time?.start?.hour)}:${to2(time?.start?.minute)}">
    <label for="end${id}"> ถึง </label>
    <input id="te${id}" name="end${id}" type="time" value="${to2(time?.end?.hour)}:${to2(time?.end?.minute)}">
    <button class="icon" onclick="removeTimeItem(${id})">
      <svg xmlns="http://www.w3.org/2000/svg" height="18" viewBox="0 96 960 960" width="18">
        <path
          d="M261 936q-24 0-42-18t-18-42V306h-11q-12.75 0-21.375-8.675-8.625-8.676-8.625-21.5 0-12.825 8.625-21.325T190 246h158q0-13 8.625-21.5T378 216h204q12.75 0 21.375 8.625T612 246h158q12.75 0 21.375 8.675 8.625 8.676 8.625 21.5 0 12.825-8.625 21.325T770 306h-11v570q0 24-18 42t-42 18H261Zm0-630v570h438V306H261Zm106 454q0 12.75 8.675 21.375 8.676 8.625 21.5 8.625 12.825 0 21.325-8.625T427 760V421q0-12.75-8.675-21.375-8.676-8.625-21.5-8.625-12.825 0-21.325 8.625T367 421v339Zm166 0q0 12.75 8.675 21.375 8.676 8.625 21.5 8.625 12.825 0 21.325-8.625T593 760V421q0-12.75-8.675-21.375-8.676-8.625-21.5-8.625-12.825 0-21.325 8.625T533 421v339ZM261 306v570-570Z" />
      </svg>
    </button>
  </div>
  `

const timeListMapper = () => {
    timeListDisplay.innerHTML = timeList.map((it, index) => {
        const html = timeItemTemplate(index, it)
        return html
    }).join(" ")
}

const removeTimeItem = (id) => {
    timeList.splice(id, 1)
    timeListMapper()
}
)==";


static const char main2[] PROGMEM =
R"==(
const addTimeItem = () => {
    const id = timeList.length

    timeList.push({ start: {}, end: {} })
    timeListMapper()
    $(`ts${id}`).onchange = e => {
        const t = e.target.value
        console.log(t)
        timeList[id].start.hour = parseInt(t.slice(0, 2))
        timeList[id].start.minute = parseInt(t.slice(3, 5))
    }
    $(`te${id}`).onchange = e => {
        const t = e.target.value
        console.log(t)
        timeList[id].end.hour = parseInt(t.slice(0, 2))
        timeList[id].end.minute = parseInt(t.slice(3, 5))
    }
}


$('s1').onchange = e => swapConfig.every.hour = parseInt(e.target.value)
$('s2').onchange = e => swapConfig.every.minute = parseInt(e.target.value)
$('s3').onchange = e => swapConfig.for.hour = parseInt(e.target.value)
$('s4').onchange = e => swapConfig.for.minute = parseInt(e.target.value)

const update = () => {
    swapDisplay.hidden = mode
    timeDisplay.hidden = !mode

    if (mode) {
        rail.children[0].classList.add('active')
        rail.children[1].classList.remove('active')
    } else {
        rail.children[0].classList.remove('active')
        rail.children[1].classList.add('active')
    }
}

const toggleMode = () => {
    mode = !mode
    update()
}

const init = () => {
    $('s1').value = swapConfig.every.hour
    $('s2').value = swapConfig.every.minute
    $('s3').value = swapConfig.for.hour
    $('s4').value = swapConfig.for.minute
    timeListMapper()
    update()
}

init()

)==";


static const char notfoundHtml[] PROGMEM =
R"==(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="app.css">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Not found</title>
</head>
<body>
    <div class="notfound">
        <div>
            <h2> 404 </h2>
            <p> Not found</p>
        </div>
    </div>
</body>
</html>
)==";


}
