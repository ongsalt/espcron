const prefixURL = 'http://192.168.153.220'
let headers = new Headers({
    "Accept": "application/json",
    "Content-Type": "application/json",
    "User-Agent": "espcron-web"
});

const postHeader = {
    // mode: 'no-cors',
    method: 'POST',
    headers
}

const getHeader = {
    // mode: 'no-cors',
    method: 'GET',
    headers
}

const API = {
    to2(it) {
        if (it < 10) {
            return `0${it}`
        }
        return `${it}`
    },
    async setMode(mode) {
        const res = await fetch(`${prefixURL}/api/mode/${mode ? 1 : 0}`, postHeader)
        console.log(await res.text())
        return res
    },
    async addTime(time) {
        const url = `${prefixURL}/api/on/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },
    async removeTime(time) {
        const url = `${prefixURL}/api/remove/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },
    async setEvery(time) {
        const url = `${prefixURL}/api/every/${to2(time.start.hour)}${to2(time.start.minute)}/for/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },
    async getMode() {
        const url = `${prefixURL}/api/mode`
        console.log(url)
        const res = await fetch(url, getHeader)
        const data = await res.json()
        return data
    },
    async getEvery() {
        const url = `${prefixURL}/api/every`
        console.log(url)
        const res = await fetch(url, getHeader)
        console.log(res)
        const data = await res.json()
        return data
    },
    async getPeriod() {
        const url = `${prefixURL}/api/period`
        console.log(url)
        const res = await fetch(url, getHeader)
        const data = await res.json()
        return data.data
    },

}