function Carregar() {
    var msg = window.document.getElementById('msg')
    var img = window.document.getElementById('img')
    var ft = window.document.getElementById('ft')
    var data = new Date()
    var hora = data.getHours()
    msg.innerHTML = `Agora são ${hora} horas`

    if (hora >= 0 && hora < 12) {
        //BOM DIA
        ft.src = 'img/manha.png'
        document.body.style.background = "#eeeb38"
    }

    else if (hora >= 12 && hora < 18) {
        //BOA TARDE
        ft.src = 'img/tarde.png'
        document.body.style.background = "#dd6809"
    }

    else {
        //BOA NOITE
        ft.src = 'img/noite.png'
        document.body.style.background = "#331258"
    }
}
