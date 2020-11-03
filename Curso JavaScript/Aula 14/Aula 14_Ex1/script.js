var inputBegin = document.getElementById('begin')
var inputEnd = document.getElementById('end')
var inputPass = document.getElementById('pass')
var result = document.getElementById('res')

function verify() {

    var begin = Number.parseInt(inputBegin.value)
    var end = Number.parseInt(inputEnd.value)
    var pass = Number.parseInt(inputPass.value)

    result.innerText = "  "

    if (pass > 0) {

        if (begin < 0 || end < 0 || begin == end || inputBegin.value.length == 0 || inputEnd.value.length == 0) {

            inputBegin.value = null
            inputEnd.value = null
            inputPass.value = null

            result.innerText = "Impossível contar!"
        }

        else {
                    
            // CONTAGEM CRESCENTE
            if (begin < end) {
                for (let i = begin; i <= end; i += pass) {
                    result.innerHTML += ` ${i} \u{1F449}`
                }
            }

            // CONTAGEM REGRESSIVA
            else /* begin > end */ {
                for (let i = begin; i >= end; i -= pass) {
                    result.innerHTML += ` ${i} \u{1F449}`
                }
            }

            result.innerHTML += `\u{1F3C1}`
        }
    }

    else /* pass <= 0 */ {
        inputPass.value = 1
        alert("Passo não pode ser menor ou igual a zero, mudando para 1...")
        verify()
    }

}