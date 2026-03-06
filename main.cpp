#include "game.h"

void displayMenu() {
  cout << "\n*************************" << endl;
  cout << "What would you like to do?" << endl;
  cout << "1. Look around" << endl;
  cout << "2. Pick up an item" << endl;
  cout << "3. Delete an item" << endl;
  cout << "4. Attack an enemy" << endl;
  cout << "5. View inventory" << endl;
  cout << "6. Move to another place" << endl;
  cout << "7. Quit" << endl;
  cout << "*************************" << endl;
}

int main() {
  // --------------------
  // Variables
  // --------------------
  bool gameOver = false;
  int choice;
  int itemChoice;
  int enemyChoice;
  int placeChoice;
 
  // --------------------
  // Stage creation
  // --------------------
  // Create item objects [source: https://pokemondb.net/item/all]
  Item auxPower("Aux Power", "Sharply boosts the offensive stats of a Pokémon during a battle.");
  Item berryJuice("Berry Juice", "Restores 20 health.");
  Item aspearBerry("Aspear Berry", "If held by a Pokémon, it defrosts it.");

  // Create enemy objects
  Enemy arbok("Arbok", 30, 15);
  Enemy weezing("Weezing", 50, 30);
  Enemy meowth("Meowth", 10, 5);

  // Create place objects
  Place place1("Buffalo");
  Place place2("Rochester");
  Place place3("Syracuse");

  // Add items to places
  place1.addItem(auxPower);
  place2.addItem(berryJuice);
  place2.addItem(aspearBerry);

  // Add enemies to places
  place1.addEnemy(arbok);
  place1.addEnemy(weezing);
  place3.addEnemy(meowth);

  // Connect places
  place1.addPlace(&place2);
  place2.addPlace(&place3);

  // --------------------
  // Player creation
  // --------------------
  cout << "\n*************************" << endl;
  cout << "Welcome to Pokémon World!" << endl;
  cout << "*************************" << endl;
  Player player("Pikachu", 200, 20);
  cout << "A player has been created!" << endl;
  player.moveToPlace(&place1); 

  // --------------------
  // Game start
  // --------------------
  while(!gameOver) {
    displayMenu();
    cout << "Enter choice: ";
    cin >> choice;
    cout << endl;

    switch(choice) {
      case 1: // Look around
        cout << "In " << player.currentPlace->getDesc() << "," << endl;
        player.currentPlace->printItems();
        player.currentPlace->printEnemies();
        break;
      
      case 2: // Pick up an item
        if(player.currentPlace->itemList.empty()) {
          cout << "No items to pick up in this place." << endl;
        } else {
          cout << "Choose an item to pick up (0 to cancel): " << endl;
          
          for(int i=0; i<player.currentPlace->itemList.size(); ++i) {
            cout << i+1 << ". " << player.currentPlace->itemList[i].getName() << endl;
          }
               
          cin >> itemChoice;

          if (itemChoice > 0 && itemChoice <= player.currentPlace->itemList.size()) {
            player.pickUpItem(player.currentPlace->itemList[itemChoice-1]);
            player.currentPlace->itemList.erase(player.currentPlace->itemList.begin()+itemChoice-1);
          }
        }
        break;

      case 3: // Delete an item
        if (player.displayInventory() == 0) {
          cout << "No items to delete." << endl;
        } else {
          cout << "\nChoose the item to delete (0 to cancel): " << endl;
          cin >> itemChoice;
          player.deleteItem(itemChoice);
        }
        break;

      case 4: // Attack an enemy
        if(player.currentPlace->enemyList.empty()) {
          cout << "No enemies to fight in this place." << endl;
        } else {
          cout << "Choose an enemy to attack (0 to cancel): " << endl;
                
          for(int i=0; i<player.currentPlace->enemyList.size(); ++i) {
            cout << i+1 << ". " << player.currentPlace->enemyList[i].getName() << endl;
          }
                
          cin >> enemyChoice;

          if(enemyChoice > 0 && enemyChoice <= player.currentPlace->enemyList.size()) {
            player.attackEnemy(player.currentPlace->enemyList[enemyChoice-1]);
            if (player.currentPlace->enemyList[enemyChoice-1].getHealth() <= 0) {
              player.currentPlace->enemyList.erase(player.currentPlace->enemyList.begin()+enemyChoice-1);
            } else {
              // The player is counterattacked by the enemy
              player.getDamage(player.currentPlace->enemyList[enemyChoice-1].getAttackPower());
            }
          }
        }
        break;

      case 5: // View inventory
        player.displayInventory();
        break;

      case 6: // Move to another place
        if (player.currentPlace->placeList.empty()) {
          cout << "This is the end of the world!" << endl;
        } else {
          cout << "Choose a place to move to (0 to cancel): " << endl;
          
          for (int i=0; i<player.currentPlace->placeList.size(); ++i) {
            cout << i+1 << ". " << player.currentPlace->placeList[i]->getDesc() << endl;
          }
                
          cin >> placeChoice;

          if (placeChoice > 0 && placeChoice <= player.currentPlace->placeList.size()) {
            player.moveToPlace(player.currentPlace->placeList[placeChoice-1]);
          }
        }
        break;

      case 7: // Quit
        cout << "Thanks for playing!" << endl;
        gameOver = true;
        break;

      default:
        cout << "Invalid choice, please try again." << endl;
        break;
    }
  }

  return 0;
}
