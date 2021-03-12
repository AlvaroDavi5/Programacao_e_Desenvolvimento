function computingC() {

    //introduzir notas e converter variáveis de notas
    var cRed = window.prompt('Nota da Redação:')
    var cCN = window.prompt('Nota de Naturais:')
    var cCH = window.prompt('Nota de Humanas:')
    var cLin = window.prompt('Nota de Linguagens:')
    var cMat = window.prompt('Nota de Matemática:')

    parseInt.cRed
    parseInt.cCN
    parseInt.cCH
    parseInt.cLin
    parseInt.cMat

    //var de pesos e converter
    var cPs = 15
    var cPr = 4
    var cPcn = 3
    var cPch = 1
    var cPl = 2
    var cPm = 5

    parseInt.cPs
    parseInt.cPr
    parseInt.cPcn
    parseInt.cPch
    parseInt.cPl
    parseInt.cPm

    //contagem
    var cN = ((cPr * cRed) + (cPcn * cCN) + (cPch * cCH) + (cPl * cLin) + (cPm * cMat)) / cPs
    
    cN.toString

    //resultado
    window.document.write('A média da sua nota para o curso de C. da Computação é de: ' + cN)

}

function biologicC() {

    //introduzir notas e converter variáveis de notas
    var bRed = window.prompt('Nota da Redação:')
    var bCN = window.prompt('Nota de Naturais:')
    var bCH = window.prompt('Nota de Humanas:')
    var bLin = window.prompt('Nota de Linguagens:')
    var bMat = window.prompt('Nota de Matemática:')

    parseInt.bRed
    parseInt.bCN
    parseInt.bCH
    parseInt.bLin
    parseInt.bMat

    //var de pesos e converter
    var bPs = 15
    var bPr = 4
    var bPcn = 4
    var bPch = 2
    var bPl = 2.5
    var bPm = 2.5

    parseInt.bPs
    parseInt.bPr
    parseInt.bPcn
    parseInt.bPch
    bPl.toFixed(1)
    bPm.toFixed(1)
    

    //contagem
    var bN = ((bPr * bRed) + (bPcn * bCN) + (bPch * bCH) + (bPl * bLin) + (bPm * bMat)) / bPs
    
    bN.toString

    //resultado
    window.document.write('A média da sua nota para o curso de C. Biológicas é de: ' + bN)

}
