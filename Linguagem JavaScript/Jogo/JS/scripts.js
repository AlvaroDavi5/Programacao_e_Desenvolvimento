// onmousemove move Dino

var dino = window.document.getElementById('dino')

document.addEventListener('mousemove', function(e) {

    var x = e.clientX
    var y = e.clientY
    dino.style.left = x + 'px'
    dino.style.top = y + 'px'

})

// onkeypress move T-Rex

var Trex = window.document.getElementById('Trex')

var topPosition = 0
var leftPosition = 0

function TrexMov(e) {
    
    //up (W)
    if (e.keyCode == 87) {
        topPosition -= 7
        Trex.style.top = (parseInt(topPosition) + topPosition) + 'px'
    }

    //down (S)
    if (e.keyCode == 83) {
        topPosition += 7
        Trex.style.top = (parseInt(topPosition) + topPosition) + 'px'
    }

    //left (A)
    if (e.keyCode == 65) {
        leftPosition -= 7
        Trex.style.left = (parseInt(leftPosition) + leftPosition) + 'px'
    }

    //right (D)
    if (e.keyCode == 68) {
        leftPosition += 7
        Trex.style.left = (parseInt(leftPosition) + leftPosition) + 'px'
    }

}

document.onkeydown = TrexMov
