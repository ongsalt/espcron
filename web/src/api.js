const prefixURL = '192.168.153.220'
const apiHeader = {}

const API = {
    to2(it) {
        if (it < 10) {
            return `0${it}`
        }
        return `${it}`
    },
    async setMode(mode) {
        const res = await fetch(`http://${prefixURL}/api/mode/${mode ? 1 : 0}`, {
            mode: 'no-cors'
        })
        console.log(await res.text())
        return res
    },
    async addTime(time) {
        const url = `http://${prefixURL}/api/on/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url, { mode: 'no-cors' })
    },
    async removeTime(time) {
        const url = `http://${prefixURL}/api/remove/${to2(time.start.hour)}${to2(time.start.minute)}/to/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url, { mode: 'no-cors' })
    },
    async setEvery(time) {
        const url = `http://${prefixURL}/api/every/${to2(time.start.hour)}${to2(time.start.minute)}/for/${to2(time.end.hour)}${to2(time.end.minute)}`
        console.log(url)
        return await fetch(url, { mode: 'no-cors' })
    },

}