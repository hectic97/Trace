time_end = true;

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
            document.querySelector('h1').innerText = `${hour}:${min}:${sec}`;
            document.getElementById('hour').value = hour;
            document.getElementById('min').value = min;
            document.getElementById('sec').value = sec;
        }
        else{
            time_end = true;
            document.getElementById('countdown').style.display = 'none';
            // clearInterval(x);
            
            
        }
    }
    
}

function start(){
    time_end = false;
    console.log('start');
    var x = setInterval(countdown,1000);
}