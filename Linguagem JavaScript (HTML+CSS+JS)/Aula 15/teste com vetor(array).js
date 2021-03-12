/*

As posições dos vetores(arrays) são chamadas de "elementos" e são enumeradas por valores chamados 'chaves' ou 'índices', cada elemento pode receber um `conteúdo`.

a = [e0, e1, e2, e3]

e0 = 2
e1 = 5
e2 =      (vazio)
e3 = 7

*/

let numbs = [5, 9, 7]

console.log(numbs)
console.log(numbs[2])
console.log(numbs[0])
console.log(numbs[1])
console.log("Um quarto valor foi acrescentado à posição '3' do vetor. \n")
numbs[3] = 1
console.log("Um novo valor será acrescentado à última posição do vetor. \n")
numbs.push(3)
console.log(`O vetor completo agora é ${numbs}. \nE tem o comprimento de ${numbs.length} elementos.`)
console.log("Organizando de forma crescente, o vetor fica: " + numbs.sort()) // 'sort' é uma função, portanto necessita de parênteses
