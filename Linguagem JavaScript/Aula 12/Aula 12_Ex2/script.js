// IMC = P + A*A

function initCalc() {

    var Weigth = document.getElementById('weigth')
    var Height = document.getElementById('height')
    // var Button = document.getElementById('button')
    var Result = document.getElementById('result')

    var P = Number.parseFloat(Weigth.value)
    var A = Number.parseFloat(Height.value)
    var Res = P / (A*A)
    var IMC = Number.parseInt(Res)
    
    if (IMC < 17) {
        Cat = "Você está muito abaixo do seu peso ideal"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }

    else if (IMC >= 17 && IMC < 19) {
        Cat = "Você está abaixo do seu peso ideal"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }

    else if (IMC >= 19 && IMC < 25) {
        Cat = "Você está no seu peso ideal"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }

    else if (IMC >= 25 && IMC < 30) {
        Cat = "Você está acima do seu peso ideal"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }
    
    else if (IMC >= 30 && IMC < 35) {
        Cat = "Você está com Obesidade (Ob. I)"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }
    
    else if (IMC >= 35 && IMC < 40) {
        Cat = "Você está com Obesidade Severa (Ob. II)"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }
    
    else if (IMC >= 40) {
        Cat = "Você está com Obesidade Mórbida (Ob. III)"
        Result.innerText = `Seu Índice de Massa Corpórea é: ${IMC}`
    }

    else {
        Cat = 'Por favor, insira os dados e tente novamente!'
        Result.innerText = ` `
    }

    alert(Cat)
}
