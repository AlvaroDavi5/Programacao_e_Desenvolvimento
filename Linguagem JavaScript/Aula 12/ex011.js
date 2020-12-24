var idade = 17
console.log(`Você tem ${idade} anos.`)

if (idade < 16) {
    console.log("Não vota")
}

/*
if (idade >= 16 && idade < 18) {
    console.log("voto opcional")
}
*/

else if (idade < 18) {
    console.log("Voto opcional")
}


else {
    console.log("Voto obrigatório")
}

/*
else {

    if (idade >= 16 && idade < 18) {
        console.log("Voto opcional")
    }

    else {
        console.log("Voto obrigatório")
    }
}
*/