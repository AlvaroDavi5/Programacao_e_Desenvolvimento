var idade = 18

function idadeVerif() {

    switch (idade) {
        case (idade < 18):
            console.log("Menor de Idade")
            break
        case (idade = 18):
            console.log("Tem 18 anos")
            break
        default:
            console.log("Tem Mais de 18 Anos")
            break
    }

}

idadeVerif()