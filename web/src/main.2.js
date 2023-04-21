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

const toggleMode = (value) => {
    if (value != mode) {
        API.setMode(value)
        mode = value
        update()
    }
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
