time_end = true;
var ring = new Audio();
ring.src = "bbb.mp3";
function timeToString(time){
    if(time < 10){
        return `0`+String(time);
    }
    return String(time);
}
function countdown(){
    if (!time_end)
    {
        var hour = parseInt(document.getElementById('hour').value);
        var min = parseInt(document.getElementById('min').value);
        var sec = parseInt(document.getElementById('sec').value);
        if (hour || min || sec){
            var time = 3600 * hour + 60 * min + sec;
            time--;
            console.log(time);
            hour = parseInt(time / 3600);
            min = parseInt((time - hour * 3600) / 60);
            sec = time - 3600 * hour - 60 * min;
            document.querySelector('h1').innerText = timeToString(hour)+':'+timeToString(min)+
            ':'+timeToString(sec);
            document.getElementById('hour').value = hour;
            document.getElementById('min').value = min;
            document.getElementById('sec').value = sec;
        }
        else{
            time_end = true;
            document.querySelector('h1').innerText = 'TIME OUT';
            ring.play();
            // clearInterval(x);

            
            
        }
    }
    
}

function start(){
    time_end = false;
    console.log('start');
    var hour = parseInt(document.getElementById('hour').value);
    var min = parseInt(document.getElementById('min').value);
    var sec = parseInt(document.getElementById('sec').value);
    document.querySelector('h1').innerText = timeToString(hour)+':'+timeToString(min)+
            ':'+timeToString(sec);
    document.getElementById('set').innerText = 'Reset Timer';
    document.getElementById('set').removeEventListener("click",set);
    document.getElementById('set').addEventListener("click",function(){
        window.location.reload();
    })
    // document.getElementById('set').style.display = 'none';
    document.querySelector('.js_setTime').style.display = 'none';
    
    var x = setInterval(countdown,1000);
}
var e = document.getElementById('set').addEventListener("click",start);