let runPosit = ['Marcos', 'Lana', 'Rose', 'Julien', 'Bob', 'James']

for(i = 0; i < runPosit.length; i++) {
    console.log(`${i+1} - ` + runPosit[i])
}

// ##############################################

let num = [3, 9, 4, 1, 8]

for (let pos in num) /* PARA CADA pos EM num */ {
    num.sort() // Organizar em ordem crescente
    console.log(`A posição ${pos} tem o valor ${num[pos]}`)
}

// Para buscar um valor dentro do array, retornando seu índice

console.log(`O valor 9 está na posição: ${num.indexOf(9)}`)


let findValue = num.indexOf(2) // O número não existe, portanto ele vai retornar o valor '-1', que é uma posição inexistente em vetores (que começam em 0)

if (findValue == -1) {
    console.log("Valor não encontrado!")
}
else {
    console.log(findValue)
}