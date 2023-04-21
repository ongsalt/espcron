const $ = (id) => document.getElementById(id)

const rail = $('rail')
const swapDisplay = $('swap-mode')
const timeDisplay = $('time-mode')
const timeListDisplay = $('list')
const timeDiff = []

// let mode = |mode|
let mode = true
let isLoading = true

let swapConfig = {
    every: {
        hour: 2,
        minute: 30
    },
    for: {
        hour: 1,
        minute: 15
    }
}

let timeList = [
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
    API.removeTime(timeList[id])
    timeList.splice(id, 1)
    timeListMapper()
}