var num = 5

for (i = 0; i <= num; i++) /* Iniciação; Teste lógico; Finalização */ {
    console.log(i);
}
console.log("fim")

// ----------------------------------------------

var objeto = {

    tamanho: '12 cm',
    cor: ''
}

for (const cor in objeto) /* PARA CADA cor EM objeto */ {

    if (objeto.hasOwnProperty(cor)) /* Se 'objeto' tem uma propriedade chamada 'cor' */ {
        objeto.cor = 'verde'
    }
}
console.log(`A cor do objeto é: ${objeto.cor}`)

// ----------------------------------------------

console.log("A quantidade de peixes variou entre: ")

var peixes = [12, 4, 7]

for (let value of peixes) /* PARA CADA valor DE peixes */ {
    console.log(value)
}

// ----------------------------------------------

var array = [1, 3, 5, 9]

array.forEach(element => /* PARA CADA elemento DO array */ {
    console.log("Oi!")
});

console.log(`Repeti ${array.length} vezes pois o vetor '${array}' possui ${array.length} posições`)