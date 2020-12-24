var list = document.querySelector('select#selectList')
var res = document.querySelector('div#res')
var listaNum = []

function getNum() {

	inputNum = document.getElementById('inpnumb')
	tempNum = Number(inputNum.value)

	if (isNumb(tempNum)) {
		if (!inList(tempNum, listaNum)) {
			res.innerHTML = ''
			listaNum.push(tempNum)
			// list.innerHTML += `<option> Valor inserido: ${tempNum} </option>`
			let item = document.createElement('option')
			item.text = `Valor inserido: ${tempNum}`
			list.appendChild(item)
		}
		else {
			window.alert('ERRO: valor já se encontra na lista!')
		}
	}
	else {
		window.alert('ERRO: digite um valor válido!')
	}

	inputNum.value = ''
	inputNum.focus()
}

function setValue() {

	if (listaNum.length == 0) {
		window.alert('Você precisa adicionar valores antes de finalizar')
	}
	else {

		let lista = listaNum
		let minor = listaNum[0]
		let major = listaNum[0]
		let soma = 0
		let media = 0

		for (let pos in listaNum) {
			if (listaNum[pos] > major) {
				major = listaNum[pos]
			}
			if (listaNum[pos] < minor) {
				minor = listaNum[pos]
			}
			soma += listaNum[pos]
			media = (soma / lista.length)
		}

		res.innerHTML = ''
		res.innerHTML += `</br> Total de números registrados: ${lista.length} </br>`
		res.innerHTML += `</br> Menor valor: ${minor}, maior valor: ${major} </br>`
		res.innerHTML += `</br> Soma de todos os valores: ${soma}, média de todos os valores: ${media} </br>`
		res.innerHTML += `</br> Elementos em ordem de adição: </br> ${lista} </br>`
		res.innerHTML += `</br> Elementos em ordem de caractere: </br> ${lista.sort()} </br>`
	}

}

function inList(num, lis) {
	if (lis.indexOf(num) != -1) {
		return true
	}
	else {
		return false
	}
}

function isNumb(num) {
	if (num >= 1 && num <= 100) {
		return true
	}
	else {
		return false
	}
}