const clockContainer = document.querySelector(".js-clock");
const clockTitle = clockContainer.querySelector("h1");
function fixTimeLength(time){
    if (time < 10){
        time = `0` + time;
    };
    return time;
}
function getTime(){
    const date = new Date();
    const minutes = fixTimeLength(date.getMinutes());
    const hours = fixTimeLength(date.getHours());
    const seconds = fixTimeLength(date.getSeconds());
    clockTitle.innerText = `${hours}:${minutes}:${seconds}`;
}

function init() {
    getTime();
    setInterval(getTime,1000);
}

init();