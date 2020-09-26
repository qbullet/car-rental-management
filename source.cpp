#include <iostream>
#include <string>
#include <array>

using namespace std;

// utils modules
void menuDisplay();
void selectPipe(char action);
void confirmExit();
void initials();
void backToMenu();

// rental modules
void rentalCarPipe();
void returnCarPipe();
void inputRentingCar(string member);
void rentingCar(string member, int carId, int amount, int duration);
void reportDisplay();
int addReport(string member, string carBrand, int amount, int duration);
void returnCar(int rid);
bool checkRid (int rid);

// members modules
void showMembers();
void addMemberPipe();
int addMemberTolist(string _name);
bool memberDuplicated (string _name);

// cars modules
void addCarPipe();
int addCarToList(string _brand, int _price);
bool carDuplicated (string _brand);
void showCars();

// class to use in this project
class Member {
  public:
    string name;
};

class Car {
  public:
    string brand;
    int price,id;
};

class CarReport {
  public:
    string brand;
    int amount, duration;
};

class Report {

  public:
    int id;
    string member;
    CarReport car;
    string status;
};

// initials
Member members[10];
int membersLength = 0;

Car cars[10];
int carsLength = 0;

Report reports[10];
int reportsLength = 0;

// Logics
int main() {
  initials();
  menuDisplay();

  return 0;
}

void initials () {
  membersLength = addMemberTolist("John");
  membersLength = addMemberTolist("Sam");
  carsLength = addCarToList("Camaro", 4500);
  carsLength = addCarToList("Mustang", 4200);
}

void menuDisplay () {
  char action;

  cout << "------ Car Rental Manager ------\n";
  cout << "1. Add member\n2. Add car\n3. Rental car\n4. Return car\n5. Report\n0. Exit\n";
  cout << "--------------------------------\n";
  cout << "select your action : ";
  cin >> action;
  
  selectPipe(action);
}

void selectPipe(char action) {
  switch (action) {
    case '1': {
      addMemberPipe();
      break;
    }
    case '2': {
      addCarPipe();
      break;
    }
    case '3': {
      rentalCarPipe();
      break;
    }
    case '4': {
      returnCarPipe();
      break;
    }
    case '5': {
      reportDisplay();
      system("pause");
      system("CLS");
      menuDisplay();
      break;
    }
    case '0': {
      confirmExit();
      break;
    }
    default: {
      cout << "you enter wrong action!\n";
      backToMenu();
      break;
    }
  }
}

void addMemberPipe () {
  string newMember;
  cout << "------ Car Rental Manager ------\n";
  cout << "Enter your new member : ";
  cin >> newMember;
  if (!memberDuplicated (newMember)) {
    membersLength = addMemberTolist(newMember);
    system("pause");
    showMembers();
    system("pause");
  } else {
    cout << newMember << " already be a member\n";
    system("pause");
    addMemberPipe();
  }

  system("CLS");
  menuDisplay();
}

void addCarPipe () {
  string newCar;
  cout << "------ Car Rental Manager ------\n";
  cout << "Enter your new car : ";
  cin >> newCar;
  if (!carDuplicated (newCar)) {
    int newPrice = 0;
    cout << "Enter price for " << newCar << " : ";
    cin >> newPrice;
    carsLength = addCarToList(newCar, newPrice);
    system("pause");
    showCars();
    system("pause");
  } else {
    cout << newCar << " already be in list\n";
    system("pause");
    addCarPipe();
  }

  system("CLS");
  menuDisplay();
}

void rentalCarPipe() {
  string member;
  cout << "Enter name of member : ";
  cin >> member;
  if (memberDuplicated (member)) {
    inputRentingCar(member);
  } else {
    cout << member << " not be a member, register before use this service\n";
    backToMenu();
  }
}

void inputRentingCar(string member) {
  showCars();
  int durationInput, amount = 0;
  int carSelected;
  cout << "Select car(ID) : ";
  cin >> carSelected;
  cout << "Enter amount of car : ";
  cin >> amount;
  cout << "Enter duration(days) : ";
  cin >> durationInput;
  
  if (carSelected <= carsLength &&  amount != 0 && durationInput != 0) {
    rentingCar(member, carSelected, amount, durationInput);
  } else {
    cout << "You just input useless options, pls try again\n";
    system("pause");
    system("CLS");
    inputRentingCar(member);
  }
}

void rentingCar(string member, int carId, int amount, int duration) {
  Car car = cars[carId-1];
  char choice;
  cout << "Your cost is " << car.price*amount*duration << "  baht, Do you want to continue(Y or N) : ";
  cin >> choice;
  if (choice == 'Y' ||choice == 'y') {
    reportsLength = addReport(member, car.brand, amount, duration);
    reportDisplay();
    backToMenu();
  } else if (choice == 'N' ||choice == 'n') {
    cout << "Your transaction has been cancel, going to mainmenu\n";
    backToMenu();
  } else {
    cout << "no such command as " << choice << " try again.\n";
    system("pause");
    system("CLS");
    rentingCar(member, carId, amount, duration);
  }
  
}

void returnCarPipe() {
  reportDisplay();
  int rid;
  cout << "Enter your RID : ";
  cin >> rid;

  returnCar(rid);
}

void returnCar(int rid) {
  if (checkRid(rid)) {
    reports[rid-1].status = "returned";
    cout << "["<< reports[rid-1].member << "] has return [" << reports[rid-1].car.brand << "]\n";
    backToMenu();
  } else {
    cout << "cant find this RID, please try again\n";
    system("pause");
    system("CLS");
    returnCarPipe();
  }
  
}

bool checkRid (int rid) {
  for (int index = 0; index < reportsLength; index++) {
    if (reports[index].id == rid) {
      return true;
    }
  }

  return false;
}

int addReport(string member, string carBrand, int amount, int duration) {
  reports[reportsLength].id = reportsLength+1;
  reports[reportsLength].member = member;
  reports[reportsLength].car.brand = carBrand;
  reports[reportsLength].car.amount = amount;
  reports[reportsLength].car.duration = duration;
  reports[reportsLength].status = "renting";
  reportsLength++;
  
  return reportsLength;
}

int addMemberTolist (string _name) {
  members[membersLength].name = _name;
  membersLength++;
  cout << _name << " has been added\n";

  return membersLength;
}

bool memberDuplicated (string _name) {
  for (int index = 0; index < membersLength; index++) {
    if (members[index].name == _name) {
      return true;
    }
  }

  return false;
}

void showMembers () {
  system("cls");
  cout << "------ Car Rental Manager ------\n";
  cout << "Members : \n";
  for (int index = 0; index < membersLength; index++) {
    cout << "[" << index+1 << "] : " << members[index].name << endl;
  }
  cout << "--------------------------------\n";
}

int addCarToList ( string _brand, int _price ) {
  cars[carsLength].id = carsLength+1;
  cars[carsLength].brand = _brand;
  cars[carsLength].price = _price;
  carsLength++;
  cout << _brand << " has been added\n";

  return carsLength;
}

bool carDuplicated (string _brand) {
  for (int index = 0; index < carsLength; index++) {
    if (cars[index].brand == _brand) {
      return true;
    }
  }

  return false;
}

void showCars () {
  system("cls");
  cout << "------ Car Rental Manager ------\n";
  cout << "Cars : \n";
  for (int index = 0; index < carsLength; index++) {
    cout << "[" << cars[index].id << "] : " << cars[index].brand << "(" << cars[index].price << "baht)\n";
  }
  cout << "--------------------------------\n";
}

void reportDisplay() {
  system("cls");
  cout << "------ Car Rental Manager ------\n";
  cout << "Rentals Report : \n";
  for (int index = 0; index < reportsLength; index++) {
    cout << "(" << reports[index].status << ")" << " RID:" << reports[index].id << " -> [" << reports[index].car.amount << " "; 
    cout << reports[index].car.brand << "] has been rented by [" << reports[index].member << "] for [" << reports[index].car.duration << " day(s)]\n";
  }
  cout << "--------------------------------\n";
}

void backToMenu() {
  system("pause");
  system("CLS");
  menuDisplay();
}

void confirmExit () {
  char confirm;
  cout << "Are you sure to exit(Y or N)!: ";
  cin >> confirm;
  if (confirm == 'Y' || confirm == 'y') {
    exit(0);
  } else if ((confirm == 'N' || confirm == 'n')) {
    menuDisplay();
  } else {
    cout << "no such command as '" << confirm << "'\n";
    system("pause");
    confirmExit();
  }
}
