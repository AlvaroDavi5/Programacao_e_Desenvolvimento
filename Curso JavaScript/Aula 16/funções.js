/*

    Toda função pode ter:
        ~ Chamada
        ~ Parâmetro
        ~ Ação
        ~ Retorno 

*/

var number = 8
var expoent = 2

function potencia(num = 0, exp = 0) /* Parâmetros, por padrão vêm como 0 */ {
    let res = (num ** exp) // Ação

    return res // Retorno
}

var result = potencia(number, expoent) // Chamada
console.log(result)

// ------------------------------------------------------------

function fatorial(n) {
    let fat = 1
    for (let c = n; c > 1; c--) {
        fat *= c
    }
    return fat
}
console.log(fatorial(8))

// ------------------------------------------------------------

function fat(n) {
    if (n == 1) {
        return 1
    }
    else {
        return n * fat(n - 1) // Recursividade em função
    }
}

console.log(fat(5))

/*

5! = 5 * 4 * 3 * 2 * 1
5! = 5 * 4!

n! = n * (n - 1)!
1! = 1

*/