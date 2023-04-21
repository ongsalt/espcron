const prefixURL = '192.168.153.220'
const postHeader = { 
    mode: 'no-cors',
    method: 'POST' 
}

const getHeader = { 
    mode: 'no-cors',
    method: 'GET' 
}

const API = {
    to2(it) {
        if (it < 10) {
            return `0${it}`
        }
        return `${it}`
    },
    async setMode(mode) {
        const res = await fetch(`http://${prefixURL}/api/mode/${mode ? 1 : 0}`, postHeader)
        console.log(await res.text())
        return res
    },
    async addTime(time) {
        const url = `http://${prefixURL}/api/on/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },
    async removeTime(time) {
        const url = `http://${prefixURL}/api/remove/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },
    async setEvery(time) {
        const url = `http://${prefixURL}/api/every/${to2(time.start.hour)}${to2(time.start.minute)}/for/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        const res = await fetch(url, postHeader)
        const data = await res.json()
        return data
    },    
    async getMode() {
        const url = `http://${prefixURL}/api/mode`
        console.log(url)
        const res = await fetch(url, getHeader)
        const data = await res.json()
        return data
    },
    async getEvery() {
        const url = `http://${prefixURL}/api/every`
        console.log(url)
        const res = await fetch(url, getHeader)
        const data = await res.json()
        return data
    },
    async getPeriod() {
        const url = `http://${prefixURL}/api/period`
        console.log(url)
        const res = await fetch(url, getHeader)
        const data = await res.json()
        return data
    },

}