var agora = new Date()
var DayWeek = agora.getDay()

/*
0 = Domingo/Sunday
1 = Segunda/Monday
2 = Terça/Tuesday
3 = Quarta/Wednesday
4 = Quinta/Thursday
5 = Sexta/Friday
6 = Sábado/Saturday
*/

console.log(DayWeek)

switch (DayWeek) {
    case 0:
        console.log('Hoje é Domingo')
        break
    case 1:
        console.log('Hoje é Segunda')
        break
    case 2:
        console.log('Hoje é Terça')
        break
    case 3:
        console.log('Hoje é Quarta')
        break
    case 4:
        console.log('Hoje é Quinta')
        break
    case 5:
        console.log('Hoje é Sexta')
        break
    case 6:
        console.log('Hoje é Sábado')
        break
    default:
        console.log('[ERRO] Não foi possível verificar que dia é hoje.')
        break
}
