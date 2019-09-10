#**Roguelike**

**Цель игры пройти 10 комнат и не умереть**

Только новая игра, уровень спавнится рандомно из паттернов, на предыдущий уровень можно вернуться.

**Сундук:** открыть на **Enter**, закрыть **ESC**, взять вещь в инвентарь **E**, Надеть **Space** 

**Инвентарь:** открыть **I**, закрыть **ESC**, надеть вещь **Space**, выбросить совсем **C**

**Магазин:** открыть **Enter**, купить/продать **Space**

**Читы:**
* T - top weapon
* Y - top armor
* U - random weapon
* L - level up

Все вещи деляться на 6 классов возвышения: _Обычный, редкий, эпический, легендарный, мистический и возвышенный_

Атаковать противника на Space когда они находятся на расстоянии 1 тайла.
Они вас атакуют если вы не меняете своего положения рядом с ними.

Мертвых врагов можно обыскивать также как и сундуки

## Feature (для 5 итерации)
* Предметы имеют названия
* За убийство врагов дают монетки (если их обыскать)
* Да, поверженных противников теперь можно обыскать
* Есть рюкзак, слот под оружие и 3 слота под броню (Шлем, доспех и ботинки)
* Оружие имеет урон и шанс критического урона
* Броня имеет защиту и шанс уклониться, а также до двух статов special
* Сундуки, которые можно обыскать, забрать оттуда вещи или сразу надеть на себя (ваша вещь перейдет в сундук)
* Игровое окно делится на 3 подокна: сама игра, ваше оружие, броня и статискика, а также геймлоггер
* Известная система SPECIAL 
* Магазин

## Bugs
- [ ] Перезапуск
- [ ] Уменьшение силы и вместительность инвентаря изменяются не одновременно
- [ ] Все остальные
- [ ] На уровне можно поставить несколько входов\выходов, хотя концептуально они должны быть в единственном экзмепляре
- [ ] Вывоход можно поставит рядом со стенами и при переходе через них, игрок может появится в стене
- [ ] Вход на самом  первом уровне ведет в никуда
- [ ] Система абилок вроде есть, а вроде нет (Уже просто нет)
- [X] Инвентарь не переносится на следующий уровень
- [X] Если забрать из сундука последнюю вещь с эффектами к себе в инвентарь, то эффекты не очистятся с экрана
- [X] Если два противника умрут на одной ячейке, то обыскать можно только одного, скорее всего последнего убитого (объединять в один сундук)
- [X] (Вроде больше не ломает) Пустой магазин ломает игру
- [X] Мертвый противник с пустым инвентарем отображается как пустой сундук
- [X] Переход на другой уровень иногда ломает игру
- [X] Персонаж рендрится под сундуками и прочими объектами
- [X] Еда отнимается при любом действии

## TODO
- [X] Выводить в логгер нахождение противиков
- [X] Выводить в логгер сундуки и магазины
- [X] Магазин и неписи в каком-то виде, где вы наконец сможете использовать свою харизму
- [X] Опыт за убийство
- [X] Прокачка SPECIAL за убийство врагов и перки
- [ ] Как-нибудь выделить алгоритм Брезенхама, но я не представляю как
- [ ] Ключ за деньги
- [ ] Выводить в логгер взятие предметов
- [ ] Добавить названия вещам
- [ ] Характеристика оружию: вампиризм
- [ ] Характеристика оружию: оглушение
- [ ] Зелья, свитки и тд
- [ ] Медальон с уникальными способностями
- [ ] Вечно: фиксить баги, рефакторить и улучшать стабильность
