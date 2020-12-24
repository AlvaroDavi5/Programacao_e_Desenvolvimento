// ################################### testando funcionalidade e escopo para atribuições SEM ou COM: VAR, LET e CONST ###################################

// --------------- teste de Alterabilidade ---------------

k = 0
var v = 1
let l = 2
const c = 4

k++             // ALTERADO
console.log(k)
v++             // ALTERADO
console.log(v)
l++             // ALTERADO
console.log(l)
// c++          ERRO: 'c' não pode ser alterado, pois é uma constante
console.log(c)

// --------------- teste de Escopo Funcional (em Funções) ---------------

exec = function() {
    q = 5
    var w = 6
    let e = 7
    const r = 8

    console.log(q)
    console.log(w)  // FUNCIONOU, dentro da função, para todos
    console.log(e)
    console.log(r)
}
exec()
q += 4
console.log(q)  // FUNCIONOU fora da função, nesse caso, pois mesmo em funções possui escopo global
/*
console.log(w)
console.log(e)  ERRO: o escopo dentro de uma função, para esses 3 casos, é local e não  global
console.log(r)
*/

// --------------- teste de Escopo Bloqueante (em Blocos) e Global ---------------

if (false == 0) {
    d = 10
    var x = 11
    let y = 12
    const z =13

    console.log(d)
    console.log(x)  // FUNCIONOU, dentro do bloco, para todos
    console.log(y)
    console.log(z)
}

d += 4
console.log(d)
x += 4
console.log(x)  // FUNCIONOU fora do bloco, para esses 2 casos, pois mesmo em blocos possuem escopo global
/*
console.log(y)
console.log(z)  ERRO: o escopo dentro de um bloco, para esses 2 casos, é local e não  global
*/
