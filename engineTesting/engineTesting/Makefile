CC=g++
CPPFLAGS=-Wall -g
LDFLAGS=-framework SFML -framework sfml-graphics -framework sfml-window -framework sfml-system
OBJS=CharacterSheet.o Demon.o ElucidatePalette.o Equipment.o EquipmentClass.o GameClass.o GameObjectClass.o GameObjectManager.o GameScreen.o InputModule.o InventoryClass.o InventorySheet.o Item.o LoadGameScreen.o MainMenuScreen.o OptionsScreen.o OrbClass.o PlayerClass.o Poison.o Tree.o Yang.o Yin.o goblin.o main.o spawnable.o spawner.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o


engineTest: $(OBJS)
	$(CC) -o ./engineTest $(OBJS) $(LDFLAGS)

clean:
	rm -f *.o
	rm -f ./engineTest

