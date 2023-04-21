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

const init = async () => {
    isLoading = true


    swapConfig = await API.getEvery()
    timeList = await API.getPeriod()
    const res = await API.getMode()
    console.log(res)
    mode = res.mode
    
    $('s1').value = swapConfig.every.hour
    $('s2').value = swapConfig.every.minute
    $('s3').value = swapConfig.for.hour
    $('s4').value = swapConfig.for.minute

    isLoading = false
    // unblock()

    timeListMapper()
    update()
}

const save = async () => {
    await API.resetTime()
    for (let time of timeList) {
        await API.addTime(time)
    }
}

init()
