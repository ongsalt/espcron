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