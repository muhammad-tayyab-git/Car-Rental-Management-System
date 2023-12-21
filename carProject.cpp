/*Admin
 username=tayyab
 password=668
 
 Customer
 username=asad
 password=123
 
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;
struct Customer{

	string username;//unique
	string password;
	string address;
	string phone;

};
struct Admin{

	string username;//unique
	string password;
	
};
struct Car{
	string name;//to store car name
	string modal;//to store car Modal
	string noPlate;//to store car Number Plate(unique)
	string description;//to store cars condition
	int rent;//to store rent of car per day
	int maintenanceTime;//to store number after how many times car rented,you want to send car for maintenance 
	int status;//to store availability of car
	int timesCarRented;//to store how many times a car rented
	int totalRentedHours;//to store total hours for which car is being rented
	double totalHoursRent;//to store total amount gained by a car rented
};

void displayHeader();//to show header
void menu();//to show Login Panal
void userMenu();//to show user panal
void adminMenu();//to show admin panal


int findFileSize(const string& filename);//prototype to find Number of Customers and cars
void loadAdminDataFromFile(Admin *admins,int size);//prototype to load Admin data from file into dynamic memory
void loadCustomerDataFromFile(Customer *customers,int size);//prototype to load Customer data from file into dynamic memory
void loadCarDataFromFile(Car *cars, int size);//prototype to load Car data from file into dynamic memory


void currentCustomers(Customer *customers,int size);//protype to show all the registered Customers
void currentCars(Car *cars,int size);//prototype to show all registered cars
void availableCars(Car *cars,int size);//prototype to show all the available cars 

int authenticateAdmin(Admin *admins,const string username,const string password,int size);//to check does the entered username and password for admin matched with stored data in file which is loaded in dynamic memory
int authenticateCustomer(Customer *customers,const string username,const string password,int size);//to check username and password of Customer is correc


void changeCustomerPassword(Customer *customers,int size);//to change password
void updateCustomerData(Customer *customers,int size);//to update customer data like phone address

Customer* addCustomer(Customer* customers, int& size);//to add new customer(username should be unique)And increase size of array of structure
Car* addCar(Car* cars, int& size);//to add new car(noPlate should be unique)And increase size of array of structure

Customer* removeCustomer(Customer* customers, int& size);//First check customer with provides username exists or not,if exists then remove.and decrease size of array of structure
Car* removeCars(Car* cars, int& size);//to remove car if correct noPlate is provided

void rentCar(Car *cars,int size,const string loggedUser);//to rent a car.customer can rent car for days or hours.and then generats receipt
void returnCar(Car* cars, int size, const string loggedUser);//return car if car is being rented and present in the record of rented cars

void CustomerReport(const string& fileName,string loggedUser);//to show rental history of logged customer(customer report)
void adminReport(Car *cars,int carFileSize,Customer *customers,int customerFileSize);//to show all the customers rented records(customer reports) and car inventory reports

void writeCustomerDataToFile(Customer* customers, int size);//at the end storing all the changes in customers array of structure to file
void writeCarDataToFile(Car* cars, int size);//storing all data in cars array of structure to file













int main(){
	
	int adminFileSize=findFileSize("admin.txt");
	Admin *adminPtr=new Admin[adminFileSize];
	int customerFileSize=findFileSize("customer.txt");
	Customer *customerPtr=new Customer[customerFileSize];
	int carFileSize=findFileSize("cars.txt");
	Car *carsPtr=new Car[carFileSize];
	loadAdminDataFromFile(adminPtr,adminFileSize);
	loadCustomerDataFromFile(customerPtr,customerFileSize);
	loadCarDataFromFile(carsPtr,carFileSize);
	
	
	
	displayHeader();
	int choice,userChoice,adminChoice;
	string username,password;
	

	do{
		menu();
		cout<<"Enter Your choice: ";
		cin>>choice;
		
		
		switch(choice){
			case 1:
				cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
				
                if (authenticateAdmin(adminPtr,username,password,adminFileSize)==1) {
                    cout << "\nLogin successful!\n"<<endl;
                     do{
						adminMenu();
						cout<<"Enter Your choice: ";
						cin>>adminChoice;
						switch(adminChoice){
							case 1:
								currentCustomers(customerPtr,customerFileSize);
								changeCustomerPassword(customerPtr,customerFileSize);
								writeCustomerDataToFile(customerPtr,customerFileSize);
								break;
							case 2:
								currentCustomers(customerPtr,customerFileSize); 
								currentCars(carsPtr,carFileSize); 
								cout<<endl;
								break;		
							case 3:
								customerPtr=addCustomer(customerPtr,customerFileSize);
								writeCustomerDataToFile(customerPtr,customerFileSize);
								break;
							case 4:
								currentCustomers(customerPtr,customerFileSize);
								customerPtr=removeCustomer(customerPtr,customerFileSize);
								writeCustomerDataToFile(customerPtr,customerFileSize);
								break;
							case 5:
								currentCustomers(customerPtr,customerFileSize);
								updateCustomerData(customerPtr,customerFileSize);
								writeCustomerDataToFile(customerPtr,customerFileSize);
								break;
							case 6:
								carsPtr=addCar(carsPtr,carFileSize);
								writeCarDataToFile(carsPtr,carFileSize);
								break;
							case 7:
								currentCars(carsPtr,carFileSize); 
								carsPtr=removeCars(carsPtr,carFileSize);
								writeCarDataToFile(carsPtr,carFileSize);
								break;
							case 8:
								adminReport(carsPtr,carFileSize,customerPtr,customerFileSize);
								break;
							case 9:
								cout<<"Exiting..."<<endl;
								writeCarDataToFile(carsPtr,carFileSize);
								writeCustomerDataToFile(customerPtr,customerFileSize);
								break;
							default:
								 cout << "Invalid choice! Please try again.\n";
								break;
						}
					}while(adminChoice != 9);
                    
                } else {
                    cout << "Invalid username or password for admin!\n";
                }
				break;
			case 2:
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;
				if (authenticateCustomer(customerPtr,username,password,customerFileSize)==1) {
					cout << "\nLogin successful!\n"<<endl;
                    do{
						userMenu();
						cout<<"Enter Your choice: ";
						cin>>userChoice;
						switch(userChoice){
							case 1:
							
								rentCar(carsPtr,carFileSize,username);
								writeCarDataToFile(carsPtr,carFileSize);
								break;
							case 2:
								returnCar(carsPtr,carFileSize,username);
								writeCarDataToFile(carsPtr,carFileSize);
								break;
							case 3:
								availableCars(carsPtr,carFileSize);
								break;
							case 4:
								CustomerReport("rentedCars.txt",username);
								break;
							case 5:
								cout<<"Exiting..."<<endl;
								
								writeCarDataToFile(carsPtr,carFileSize);
							
								break;
							default:
								 cout << "Invalid choice! Please try again.\n";
								break;
						}
					}while(userChoice != 5);
				}else{
					cout << "Invalid username or password for admin!\n";
				}
				break;
			case 3:
				cout<<"Exiting  programm....";
				break;
			default:
				  cout << "Invalid choice! Please try again.\n";
				  break;
		}
	}while(choice != 3);
	
	delete [] adminPtr;
	delete [] customerPtr;
	delete [] carsPtr;
	
	
	return 0;
}
//Function to show Header
void displayHeader(){
	cout<<"\t\t----------------------------------------------------------"<<endl;
	cout<<"\t\t*********//////Car Rental Management System//////*********"<<endl;
	cout<<"\t\t----------------------------------------------------------"<<endl;
}
//Function to show login panal
void menu(){
	cout<<"\n\n";
	cout<<"\t\t\t=============================\t\t\t\n";
	cout<<"\t\t\t%%%%%%%%%%  LOGIN  %%%%%%%%%%\t\t\t\n";
	cout<<"\t\t\t=============================\t\t\t\n\n\n";
	cout<<"Enter 1: Log in as Admin"<<endl;
	cout<<"Enter 2: Log in as User"<<endl;
	cout<<"Enter 3: Exit.\n"<<endl;
}
//Function to show Customer panal
void userMenu(){
	cout<<"\n\n";
	cout<<"\t\t\t======================================\t\t\t\n";
	cout<<"\t\t\t%%%%%%%%%%  CUSTOMER PANAL  %%%%%%%%%%\t\t\t\n";
	cout<<"\t\t\t======================================\t\t\t\n\n\n";
	cout<<"Enter 1: For rent"<<endl;
	cout<<"Enter 2: For return"<<endl;
	cout<<"Enter 3: For view available cars"<<endl;
	cout<<"Enter 4: For Generate report"<<endl;
	cout<<"Enter 5: For Exite.\n"<<endl;
}
//Function to show admin panal
void adminMenu(){
	cout<<"\n\n";
	cout<<"\t\t\t===================================\t\t\t\n";
	cout<<"\t\t\t%%%%%%%%%%  ADMIN PANAL  %%%%%%%%%%\t\t\t\n";
	cout<<"\t\t\t===================================\t\t\t\n\n\n";
	cout<<"Enter 1: For Change Password"<<endl;
	cout<<"Enter 2: For View current registered Customers and Cars"<<endl;
	cout<<"Enter 3: For add customer"<<endl;
	cout<<"Enter 4: For remove customer"<<endl;
	cout<<"Enter 5: For update customer data"<<endl;
	cout<<"Enter 6: For add cars"<<endl;
	cout<<"Enter 7: For remove cars"<<endl;
	cout<<"Enter 8: For Generate reports"<<endl;
	cout<<"Enter 9: For Exite.\n"<<endl;
}
//Function to find Number of Customers and cars
int findFileSize(const string& filename){
	int size=0;
	ifstream inFile(filename);
	if(!inFile){
		cout<<"Error opening File.";
		return size;
	}
	
	string line;
	while(getline(inFile,line)){
		size++;
	}
	return size;
	
}
//Function to load Admin data from file into dynamic memory
void loadAdminDataFromFile(Admin *admins,int size){
	ifstream inFile("admin.txt");
    if (inFile.is_open()) {
        for (int i = 0; i < size; i++) {
            string line;
            if (getline(inFile, line)) {
                stringstream ss(line);
                getline(ss, admins[i].username, ',');
                getline(ss, admins[i].password);
               
               

              
                if (ss.fail()) {
                    cout << "Error reading data from file(loadAdminDataFromFile).\n";
                    break;
                }
            } else {
                cout << "Error reading line from file(loadAdminDataFromFile).\n";
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Error in opening File.\n";
        return;
    }
}
//Function to load Customer data from file into dynamic memory
void loadCustomerDataFromFile(Customer *customers,int size){
	ifstream inFile("customer.txt");
    if (inFile.is_open()) {
        for (int i = 0; i < size; i++) {
            string line;
            if (getline(inFile, line)) {
                stringstream ss(line);
                getline(ss, customers[i].username, ',');
                getline(ss, customers[i].password, ',');
                getline(ss, customers[i].address, ',');
                getline(ss, customers[i].phone);
              
               

              
                if (ss.fail()) {
                    cout << "Error reading data from file.(loadCustomerDataFromFile)\n";
                    break;
                }
            } else {
                cout << "Error reading line from file.(loadCustomerDataFromFile)\n";
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Error in opening File.\n";
        return;
    }
}
//Function to load Car data from file into dynamic memory
void loadCarDataFromFile(Car *cars, int size) {
    ifstream inFile("cars.txt");
    if (inFile.is_open()) {
        for (int i = 0; i < size; ++i) {
            string line;
            if (getline(inFile, line)) {
                stringstream ss(line);
                string rentStr,maintenanceTimeStr,statusStr,timesCarRentedStr,totalRentedHoursStr,totalHoursRentStr;
                getline(ss, cars[i].name, ',');
                getline(ss, cars[i].modal, ',');
                getline(ss, cars[i].noPlate, ',');
				getline(ss, cars[i].description, ',');
               
				getline(ss, rentStr, ',');
				getline(ss, maintenanceTimeStr, ',');
				getline(ss, statusStr,',');
				getline(ss, timesCarRentedStr,',');
				getline(ss, totalRentedHoursStr,',');
				getline(ss, totalHoursRentStr);
                cars[i].rent = stoi(rentStr);
                cars[i].maintenanceTime = stoi(maintenanceTimeStr);
                cars[i].status = stoi(statusStr);
                cars[i].timesCarRented = stoi(timesCarRentedStr);
                cars[i].totalRentedHours = stoi(totalRentedHoursStr);
                cars[i].totalHoursRent = stod(totalHoursRentStr);
             

                if (ss.fail()) {
                    cout << "Error reading data from file.(loadCarDataFromFile)\n";
                    break;
                }
            } else {
                cout << "Error reading line from file.(loadCarDataFromFile)\n";
                break;
            }
        }
        inFile.close();
    } else {
        cout << "Error in opening File.\n";
        return;
    }
}
//Function to show all the registered Customers
void currentCustomers(Customer *customers,int size){
	cout<<"\n\n";
	cout<<"\t\t\t--------------------\t\t\t\n";
	cout<<"\t\t\tRegistered Customers" << endl;
	cout<<"\t\t\t--------------------\t\t\t\n";
	int check=0;
	cout << left << setw(10) << "Name" << left << setw(20) << "Address" << left << setw(15) << "Phone" << endl;
	for (int i = 0; i < size; ++i) {
		cout << left << setw(10) << customers[i].username << left << setw(20) << customers[i].address << left << setw(15) << customers[i].phone << endl;
		check++;
	}
	if(check==0){
		cout<<"There is no Customer."<<endl;
		return;
	}
	cout<<"\n\n";
}
//Function to show all the registered Cars
void currentCars(Car *cars,int size){
	cout<<"\n\n";
	cout<<"\t\t\t---------------\t\t\t\n";
	cout<<"\t\t\tRegistered Cars" << endl;
	cout<<"\t\t\t---------------\t\t\t\n";
	int check=0;
	cout << left << setw(15) << "Car" << setw(15) << "Modal" << left << setw(15) << "NoPlate" << left << setw(10) << "Rent" << setw(10) << "Status" << endl;
	for (int i = 0; i < size; ++i) {
		cout << left  << setw(15) << cars[i].name << left << setw(15) << cars[i].modal << left << setw(15) << cars[i].noPlate << left << setw(10) << cars[i].rent << left << setw(10) << ((cars[i].status == 1) ? "Rented" : "Available") << endl;
		check++;
	}
	if(check==0){
		cout<<"There is no Car."<<endl;
		return;
	}
	cout<<"\n\n";
}
//function to show all available cars from registered cars
void availableCars(Car *cars,int size){
	cout<<"\n\n";
	cout<<"\t\t\t--------------\t\t\t\n";
	cout<<"\t\t\tAvailable Cars" <<endl;
	cout<<"\t\t\t--------------\t\t\t\n";
	int check=0;
	cout << left << setw(15) << "Car" << left << setw(20) << "Modal" << left << setw(20) << "NoPlate" << left << setw(10) << "Rent" << endl;
	for (int i = 0; i < size; ++i) {
		if (cars[i].status == 0) {
			cout << left << setw(15) << cars[i].name << left << setw(20) << cars[i].modal << left << setw(20) << cars[i].noPlate << left << setw(10) << cars[i].rent << endl;
			check++;
		}
	}
	if(check==0){
		cout<<"There is no Car."<<endl;
		return;
	}
	cout<<"\n\n";
}
//Function to check entered  username and password for Admin is correct
int authenticateAdmin(Admin *admins,const string username,const string password,int size){
	for(int i=0;i<size;i++){
		if(admins[i].username==username && admins[i].password==password){
			return 1;
		}
	}
	return -1;
	
}
//Function to check entered username and password for Customer is correct
int authenticateCustomer(Customer *customers,const string username,const string password,int size){
	for(int i=0;i<size;i++){
		if(customers[i].username==username && customers[i].password==password){
			return 1;
		}
	}
	return -1;
	
}
//Function to change password
void changeCustomerPassword(Customer *customers,int size){
	string username;
	cout<<"Enter Usrrname of Customer you want to Change Password: ";
	cin>>username;
	for(int i=0;i<size;i++){
		if(customers[i].username==username ){
		
			cout<<"Old Passord: "<<customers[i].password<<endl;
			cout<<"Enter new Passord: ";
			cin>>customers[i].password;
			cout<<"Password changed Successfully."<<endl;
			break;
		}
	}
	  
}
//function to update customer data like phone,address
void updateCustomerData(Customer *customers,int size){
	string username;
	cout<<"Enter Usrrname of Customer you want to Update Data: ";
	cin>>username;
	for(int i=0;i<size;i++){
		if(customers[i].username==username ){
			int choice;
			cout<<"Old Address: "<<customers[i].address<<endl;
			cout<<"Old Phone NUmber: "<<customers[i].phone<<endl;
			cout<<endl;
			cout<<"\nEnter 1 to update Address"<<endl;
			cout<<"Enter 2 to update phone"<<endl;
			cout<<"Enter 3 to update phone and Address"<<endl;
			cout<<"Enter 4 for Exit."<<endl;
			cout<<"Enter your choice: ";
			do{
				
				cin>>choice;
				switch(choice){
					case 1:
						cout<<"Enter New Address: ";
						cin>>customers[i].address;
						break;
					case 2:
						cout<<"Enter New Phone Number: ";
						cin>>customers[i].phone;
						break;
					case 3:
						cout<<"Enter New Address: ";
						cin>>customers[i].address;
						cout<<"Enter New Phone Number: ";
						cin>>customers[i].phone;
						break;
					default:
						break;
				} 
				if((choice==1) || choice==2 || choice==3){
					cout<<"Data Updated Successfully."<<endl;
				}else if(choice==4){
					cout<<"Exiting."<<endl;
				}else{
					cout<<"please enter correct choice.";
				}
			}while(choice !=1 && choice !=2 && choice !=3 && choice !=4);
			
			break;
		}
	}
	  
}

//function to check customer exists in file or not
int customerExists(const string username,Customer *customers,int size){
	for(int i=0;i<size;i++){
		if(customers[i].username==username){
			return 1;
		}
	}
	
	return -1;
}
//Function to add new customer.
Customer* addCustomer(Customer* customers, int& size) {
    Customer* tempCustomers = new Customer[size + 1];
    for (int i = 0; i < size; i++) {
        tempCustomers[i] = customers[i];
    }
    
    cout << "\nEnter the details of the new Customer" << endl;
    cin.ignore();

    string newUsername;
    cout << "Enter Username: ";
    do {
		
        getline(cin, newUsername);
       if(customerExists(newUsername, customers, size) != -1){
		   cout<<"Username already Exists!Enter Unique username:";
	   }
    } while (customerExists(newUsername, customers, size) != -1);

    tempCustomers[size].username = newUsername;
    
    cout << "Enter Password: ";
    getline(cin, tempCustomers[size].password);
    cout << "Enter Address: ";
    getline(cin, tempCustomers[size].address);
    cout << "Enter Phone Number(without-spaces): ";
    getline(cin, tempCustomers[size].phone);
    
    cout << "Customer Added Successfully." << endl;
    cout << endl;
    
    size++;
    delete[] customers;
    return tempCustomers;
}

//function to check  car(noPlate) exists in file or not
int carExists(const string noPlate,Car *cars,int size){
	for(int i=0;i<size;i++){
		if(cars[i].noPlate==noPlate){
			return 1;
		}
	}
	
	return -1;
}
//Function to add new car(noPlate should be unique)And increase size of array of structure
Car* addCar(Car* cars, int& size) {
	Car* tempCars = new Car[size + 1];
    for (int i = 0; i < size; i++) {
        tempCars[i] = cars[i];
    }
    
    cout << "\nEnter the details of the new Car" << endl;
    cin.ignore();
	cout << "Car Name: ";
    getline(cin, tempCars[size].name);
    cout << "Car Modal: ";
    getline(cin, tempCars[size].modal);
    string newCarNoPlate;
    cout << "Car No_Plate: ";
    do {
       getline(cin, newCarNoPlate);
       if(carExists(newCarNoPlate, cars, size) != -1){
		   cout<<"Car already Exists!Enter Unique No_plate:";
	   }
    } while (carExists(newCarNoPlate, cars, size) != -1);
	 tempCars[size].noPlate=newCarNoPlate;

    cout << "Enter Condition of Car(Like New,Normal,Good or VIP): ";
    getline(cin, tempCars[size].description);
    cout << "Enter Rent of car per Day(pkr/-): ";
    cin >> tempCars[size].rent;
	do{
	    cout<<"After how many times Car rented, You want to send Car For Maintenance(5-n):";
		cin>>tempCars[size].maintenanceTime;
	}while(tempCars[size].maintenanceTime<5);
    tempCars[size].status=0;
    tempCars[size].timesCarRented=0;
    tempCars[size].totalRentedHours=0;
    tempCars[size].totalHoursRent=0.0;
    
    cout << "Car Added Successfully." << endl;
    cout << endl;
    
    size++;
    delete[] cars;
    return tempCars;
}

//Function to remove Customer
Customer* removeCustomer(Customer* customers, int& size) {
    string customerToRemove;
    int findCustomerToRemove = -1; 
    cout << "Enter the username of the Customer You want to remove: ";
    cin >> customerToRemove;

    for (int i = 0; i < size; i++) {
        if (customers[i].username == customerToRemove) {
            findCustomerToRemove = i; 
            break; 
        }
    }

    if (findCustomerToRemove != -1) {
        Customer* tempCustomers = new Customer[size - 1];
        int tempIndex = 0;
        for (int i = 0; i < size; i++) {
            if (i != findCustomerToRemove) {
                tempCustomers[tempIndex++] = customers[i];
            }
        }
        size--;
        delete[] customers;
        cout << "Customer Removed Successfully." << endl;
        return tempCustomers;
    } else {
        cout << "Username does not Exist." << endl;
        return customers; 
    }
}

//Function to remove car
Car* removeCars(Car* cars, int& size) {
    string carToRemove;
    int findCarToRemove = -1; 
    cout << "Enter the no_plate of the Car You want to remove: ";
    cin >> carToRemove;

    for (int i = 0; i < size; i++) {
        if (cars[i].noPlate == carToRemove) {
            findCarToRemove = i; 
            break; 
        }
    }

    if (findCarToRemove != -1) {
        Car* tempCars = new Car[size - 1];
        int tempIndex = 0;
        for (int i = 0; i < size; i++) {
            if (i != findCarToRemove) {
                tempCars[tempIndex++] = cars[i];
            }
        }
        size--;
        delete[] cars;
        cout << "Car Removed Successfully." << endl;
        return tempCars;
    }else{
        cout << "Car does not Exist." << endl;
        return cars; 
    }
}
//Function to find index of car 
int FindIndexOfRentingCar(const string noPlate,Car *cars,int size){
	int findCarToRent=-1;
	 for (int i = 0; i < size; i++) {
        if (cars[i].noPlate == noPlate) {
            findCarToRent = i; 
            break; 
        }
    }
    return findCarToRent;
	
}

//Function to rent car
void rentCar(Car *cars,int size,const string loggedUser){
	cout<<"\n\n";
	cout<<"\t\t\t--------------\t\t\t\n";
	cout<<"\t\t\tAvailable Cars" <<endl;
	cout<<"\t\t\t--------------\t\t\t\n";
	int check=0;
	cout << left << setw(15) << "Car" << left << setw(15) << "Modal" << left << setw(20) << "NoPlate" << left << setw(10) << "Rent" << endl;
	for (int i = 0; i < size; ++i) {
		if (cars[i].status == 0) {
			cout << left << setw(15) << cars[i].name << left << setw(15) << cars[i].modal << left << setw(20) << cars[i].noPlate << left << setw(10) << cars[i].rent << endl;
			check++;
		}
	}
	if(check==0){
		cout<<"There is no Car."<<endl;
		return;
	}
	cout<<"\n\n";
	
	
	
	
	string rentingCarNoPlate;
	int rentingCarIndex=-1;
	cout<<"Enter the Car No_Plate You want to rent: ";
	cin>>rentingCarNoPlate;
	rentingCarIndex=FindIndexOfRentingCar(rentingCarNoPlate,cars,size);
	int days,hours;
	double rent=0.0;
	if(rentingCarIndex !=-1){
		if(cars[rentingCarIndex].status==1){
			cout<<"Car already rented."<<endl;
			return;
		}
		do{
			cout<<"Enter zero if you want to rent car for less then 1 Day.\nDon't enter negitive Number.\nEnter Number of Days You want to rent Car: ";
			cin>>days;
			if(days>0){
				hours=days*24;
				rent +=double(cars[rentingCarIndex].rent)*days;
			}
		}while(days<0);
		if(days==0){
			do{
				cout<<"Enter Number of Hours(1-24): ";
				cin>>hours;
				if(hours>=1 && hours<=24){
					rent +=((double(cars[rentingCarIndex].rent))/24)*hours;
				}
			}while(hours<1 || hours>24);
		}
		string date=__DATE__;
		string time=__TIME__;
		
		cout << "\n\n\t\tRental Receipt\t\t\t\t\n\n";
		cout << "--------------------------------------------" << endl;
		cout << left << setw(20) << "CURRENT TIME:" << right << setw(20) << time << endl;
		cout << left << setw(20) << "CURRENT DATE:" << right << setw(20) << date << endl;
		cout << left << setw(20) << "Car:" << right << setw(20) << cars[rentingCarIndex].name << endl;
		cout << left << setw(20) << "No_plate:" << right << setw(20) << cars[rentingCarIndex].noPlate << endl;
		cout << left << setw(20) << "Rent Per Day:" << right << setw(20) << cars[rentingCarIndex].rent << "Pkr" << endl;
		cout << left << setw(20) << "Amount To Be Paid:" << right << setw(20) << rent << "Pkr" << endl;
		cout << "--------------------------------------------\n\n" << endl;
		cars[rentingCarIndex].status=1;
		cars[rentingCarIndex].timesCarRented += 1;
		cars[rentingCarIndex].totalRentedHours += hours;
		cars[rentingCarIndex].totalHoursRent += rent;
		
		cout<<"Car rented Successfully."<<endl;
		
		ofstream outFile("rentedCars.txt",ios::app);
		if(!outFile){
			cout<<"Error in opening File."<<endl;
			return;
		}
		outFile<<loggedUser<<","<<cars[rentingCarIndex].name<<","<<date<<","<<time<<","<<cars[rentingCarIndex].noPlate<<","<<cars[rentingCarIndex].rent<<","<<rent<<','<<cars[rentingCarIndex].status<<endl;
		outFile.close();
		
	}else{
		cout<<"Invalid car no_plate."<<endl;
		    
    }
	
}

//Function to check car with specific noPlate exists in rented Cars File or not

bool checkCarRented(string loggedUser,string noPlate){
	
	 ifstream inFile("rentedCars.txt");
	
	 if (inFile.is_open()) {
		 string line;
		
	
		 while (getline(inFile, line)) {
			stringstream ss(line);
			 string  storedName,storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr,storedStatusStr;
			
			getline(ss, storedName, ',');
			getline(ss, storedCar, ',');
			getline(ss, storedDate, ',');
			getline(ss, storedTime, ',');
			getline(ss, storedNoPlate, ',');
			getline(ss, rentStr, ',');
			getline(ss, calculatedStr,',');
			getline(ss, storedStatusStr);
			int storedStatus=stoi(storedStatusStr);
			if(storedName==loggedUser && storedNoPlate==noPlate && storedStatus==1){
				return true;
			}
			
		
			if (ss.fail()) {
				cout << "Error reading data from file.(checkCarRented)\n";
				break;
			}
		}
		 inFile.close();
		
	 } else {
        cout << "Error in opening File.\n";
        
    }
    return false;
	
	
}

//Function to check does car with specifc noPlate is rented or not
bool checkCarStatus(Car *cars,int size,string noPlate){
	
	for(int i=0;i<size;i++){
		if(cars[i].noPlate==noPlate && cars[i].status==1){
			return true;
			
		}
	}
	
	return false;
}
//Function to update status of car in rented records file
void updateStatus(string loggedUser,string noPlate){
	ifstream inputFile("rentedCars.txt");
	ofstream outputFile("temp.txt");

	 if (inputFile.is_open() || outputFile.is_open()) {
		 string line;
		
	
		 while (getline(inputFile, line)) {
			stringstream ss(line);
			string  storedName,storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr,storedStatusStr;
			getline(ss, storedName, ',');
			getline(ss, storedCar, ',');
			getline(ss, storedDate, ',');
			getline(ss, storedTime, ',');
			getline(ss, storedNoPlate, ',');
			getline(ss, rentStr, ',');
			getline(ss, calculatedStr,',');
			getline(ss, storedStatusStr);
			int rent=stoi(rentStr);
			int calculatedRent=stoi(calculatedStr);
			int storedStatus=stoi(storedStatusStr);
			if(storedName==loggedUser && storedNoPlate==noPlate && storedStatus==1){
				storedStatus=0;
				outputFile << storedName << "," << storedCar << "," << storedDate << "," << storedTime << "," << storedNoPlate << "," << rent << "," << calculatedRent << "," << storedStatus << endl;
				cout<<"Updated";
			}else{
				outputFile << storedName << "," << storedCar << "," << storedDate << "," << storedTime << "," << storedNoPlate << "," << rent << "," << calculatedRent << "," << storedStatus << endl;
			}
		
			if (ss.fail()) {
				cout << "Error reading data from file.(checkCarRented)\n";
				break;
			}
		}
		 inputFile.close();
		 outputFile.close();
	  
		remove("rentedCars.txt");
		rename("temp.txt", "rentedCars.txt");
		
			
	} else {
			cout << "Error in opening File.\n";
			
	}

        
	
	
}

//Function to return car if car is being rented and present in the record of rented cars
void returnCar(Car* cars, int size, const string loggedUser) {
    cout << "Cars rented by you:" << endl;
    ifstream inFile("rentedCars.txt");
    int start = 1;
    if (inFile.is_open()) {
        string line;
       // string storedName, storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr;
        cout << left << setw(15) << "Car" << left << setw(15) << "Date" << left << setw(20) << "Time" << left << setw(15) << "No_Plate" << left << setw(15) << "Rent/Hour" << left << setw(15) << "Amount" << endl;

		while (getline(inFile, line)) {
			stringstream ss(line);
			string storedName, storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr,storedStatusStr;
			
			getline(ss, storedName, ',');
			getline(ss, storedCar, ',');
			getline(ss, storedDate, ',');
			getline(ss, storedTime, ',');
			getline(ss, storedNoPlate, ',');
			getline(ss, rentStr, ',');
			getline(ss, calculatedStr,',');
			getline(ss, storedStatusStr);
			
			int storedRent = stoi(rentStr);
			int storedCalculated = stoi(calculatedStr);
			int storedStatus = stoi(storedStatusStr);
			
			if (storedName == loggedUser && checkCarStatus(cars, size, storedNoPlate) && storedStatus==1) {
				cout << left << setw(15) << storedCar;
				cout << left << setw(15) << storedDate;
				cout << left << setw(20) << storedTime;
				cout << left << setw(15) << storedNoPlate;
				cout << left << setw(15) << storedRent;
				cout << left << setw(15) << storedCalculated << endl;
				start++;
			}

			if (ss.fail()) {
				cout << "Error reading data from file.(returnCar)\n";
				break;
			}
		}
        inFile.close();
    } else {
        cout << "Error in opening File.\n";
        return;
    }

    if (start != 1) {
        string noPlate;
        cout << "Enter the Number plate of Car you want to return: ";
        cin >> noPlate;
       
		
        if (checkCarRented(loggedUser, noPlate) && checkCarStatus(cars, size, noPlate)) {
            for (int i = 0; i < size; i++) {
                if (cars[i].noPlate == noPlate) {
                    cars[i].status = 0;
                    updateStatus(loggedUser,noPlate);
                    cout << "Car returned successfully." << endl;
                    break;
                }
            }
        } else {
            cout << "Enter Valid No_Plate." << endl;
        }
    } else {
        cout << "\nThere is no car rented." << endl;
    }
}

//Function to show rental history of logged customer

void CustomerReport(const string& fileName,string loggedUser){
	ifstream inFile(fileName);
	
	 if (inFile.is_open()) {
		
		int check=0;
		 string line;
		 string  storedName,storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr;
		 cout<<"\t\t\t=======================================\t\t\t\n";
		 cout<<"\t\t\t%%%%%%%%%%%  Rental Report  %%%%%%%%%%%\t\t\t\n";
		 cout<<"\t\t\t=======================================\t\t\t\n\n\n";
		 cout << left << setw(15) << "Car" << left << setw(15) << "Date" << left << setw(20) << "Time" << left << setw(15) << "No_Plate" << left << setw(15) << "Rent/Hour" << left << setw(15) << "Amount" << endl;

		while (getline(inFile, line)) {
			stringstream ss(line);
			string storedName, storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr;
			
			getline(ss, storedName, ',');
			getline(ss, storedCar, ',');
			getline(ss, storedDate, ',');
			getline(ss, storedTime, ',');
			getline(ss, storedNoPlate, ',');
			getline(ss, rentStr, ',');
			getline(ss, calculatedStr);
			
			int storedRent = stoi(rentStr);
			int storedCalculatedStr = stoi(calculatedStr);
			
			if (storedName == loggedUser) {
				cout << left << setw(15) << storedCar;
				cout << left << setw(15) << storedDate;
				cout << left << setw(20) << storedTime;
				cout << left << setw(15) << storedNoPlate;
				cout << left << setw(15) << storedRent;
				cout << left << setw(15) << storedCalculatedStr << endl;
				check++;
			}

			if (ss.fail()) {
				cout << "Error reading data from file.(CustomerReport)\n";
				break;
			}
		}
		 inFile.close();
		if(check==0){
			cout<<"\nThere is no Car rented."<<endl;
		}
	 } else {
        cout << "Error in opening File.\n";
        return;
    }
}


//Function to show rented records of all customers
void allCustomerReport(){
	ifstream inFile("rentedCars.txt");
	if (inFile.is_open()) {
		
		int check=0;
		 string line;
		 string  storedName,storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr;
		 cout << left << setw(15) <<"Customer" << left << setw(15) << "Car" << setw(15) << "Date" << setw(20) << "Time" << setw(15) << "No_Plate"
		 << setw(15) << "Rent/Hour" << setw(15) << "Amount" << endl;

		while (getline(inFile, line)) {
			stringstream ss(line);
			string storedName, storedCar, storedDate, storedTime, storedNoPlate, rentStr, calculatedStr;
			
			getline(ss, storedName, ',');
			getline(ss, storedCar, ',');
			getline(ss, storedDate, ',');
			getline(ss, storedTime, ',');
			getline(ss, storedNoPlate, ',');
			getline(ss, rentStr, ',');
			getline(ss, calculatedStr);
			
			int storedRent = stoi(rentStr);
			int storedCalculatedStr = stoi(calculatedStr);

			cout << left << setw(15) << storedName;
			cout << left << setw(15) << storedCar;
			cout << left << setw(15) << storedDate;
			cout << left << setw(20) << storedTime;
			cout << left << setw(15) << storedNoPlate;
			cout << left << setw(15) << storedRent;
			cout << left << setw(15) << storedCalculatedStr << endl;

			if (ss.fail()) {
				cout << "Error reading data from file.(allCustomerReport)\n";
				break;
			}
			check++;
		}
		 inFile.close();
		if(check==0){
			cout<<"\nThere is no Rent Record."<<endl;
		}
	 } else {
        cout << "Error in opening File.\n";
        return;
    }
}
//Functon to show admin reports
void adminReport(Car *cars,int carFileSize,Customer *customers,int customerFileSize){
	cout<<"\n\n";
	cout<<"\t\t\t=======================================\t\t\t\n";
	cout<<"\t\t\t%%%%%%%%%%  CUSTOMER REPORT  %%%%%%%%%%\t\t\t\n";
	cout<<"\t\t\t=======================================\t\t\t\n\n\n";
	allCustomerReport();
	cout<<"\n\n";
	cout<<"\t\t\t=======================================\t\t\t\n";
	cout<<"\t\t\t%%%%%%%  CAR INVENTORY REPORT  %%%%%%%%\t\t\t\n";
	cout<<"\t\t\t=======================================\t\t\t\n\n\n";
	
	cout<<"\t\t\t  -----------------------\t\t\t\n";
	cout<<"\t\t\t  INVENTORY STATUS REPORT"<<endl;
	cout<<"\t\t\t  -----------------------\t\t\t\n\n\n";

	cout << left << setw(15) << "Car" << left << setw(15) << "No_plate" << left << setw(15) << "Status" << left << setw(20) << "Condition" << left
     << setw(20) << "TimesCarRented" << left << setw(20) << "TimesCarRepaired" << left << setw(20) << "GeneratedIncome" << endl;
	for (int i = 0; i < carFileSize; i++) {
		int repaired = cars[i].timesCarRented / (cars[i].maintenanceTime);
		cout << left << setw(15) << cars[i].name;
		cout << left << setw(15) << cars[i].noPlate;
		string status = (cars[i].status == 1) ? "Rented" : "Available";
		cout << left << setw(15) << status;
		cout << left << setw(20) << cars[i].description;
		cout << left << setw(20) << cars[i].timesCarRented;
		cout << left << setw(20) << repaired;
		cout << left << setw(20) << cars[i].totalHoursRent << endl;
	}
	
	cout<<"\n\n";
	cout<<"\t\t\t ------------------\t\t\t\n";
	cout << "\t\t\t Maintenance Report" << endl;
	cout<<"\t\t\t ------------------\t\t\t\n";
	cout<<"\n\n";
	cout << left << setw(15) << "Car" << left << setw(15) << "No_Plate" << left << setw(15) << "Maintenance" << endl;
	for (int i = 0; i < carFileSize; i++) {
		cout << left << setw(15) << cars[i].name;
		cout << left << setw(15) << cars[i].noPlate;
		int maintenancePercentage = 100 - (((cars[i].timesCarRented % cars[i].maintenanceTime) * 100) / cars[i].maintenanceTime);
		cout << left << maintenancePercentage << "%" << endl;
	}
	
	
	
	cout<<"\n\n";
	cout<<"\t\t\t --------------------------\t\t\t\n";
	cout << "\t\t\t Vehicle Utilization Report" << endl;
	cout<<"\t\t\t --------------------------\t\t\t\n";
	cout<<"\n\n";
	
	cout << left << setw(20) << "Car" << left << setw(15) << "No_Plate" << left << setw(20) << "Utilization/Usage Hours" << endl;

	for (int i = 0; i < carFileSize; i++) {
		cout << left << setw(20) << cars[i].name;
		cout << left << setw(15) << cars[i].noPlate;
		cout << left << setw(20) << cars[i].totalRentedHours << endl;
	}
}
//Function to store data in to customers file
void writeCustomerDataToFile(Customer* customers, int size){
	ofstream outFile("customer.txt");
	if(!outFile){
		cout<<"Error in opening File"<<endl;
		return;
	}
	for(int i=0;i<size;i++){
			outFile << customers[i].username <<","<< customers[i].password <<","<< customers[i].address<<","<< customers[i].phone<<endl;
	}
	outFile.close();
	
}
//Function to store data in to Car file
void writeCarDataToFile(Car* cars, int size){
	ofstream outFile("cars.txt");
	if(!outFile){
		cout<<"Error in opening File"<<endl;
		return;
	}
	for(int i=0;i<size;i++){
				outFile << cars[i].name <<","<< cars[i].modal <<","<< cars[i].noPlate<<","<< cars[i].description <<","<< cars[i].rent<<","<< cars[i].maintenanceTime<<","
				<<cars[i].status<<","<< cars[i].timesCarRented<<","<< cars[i].totalRentedHours<<","<< cars[i].totalHoursRent<<endl;
	}
	outFile.close();
	
}



















