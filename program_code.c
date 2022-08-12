/* TEJESWARA SAI REDDY KARRI (TP062689) */

/* ----------------------------------------------------------HOTEL MANAGEMENT SYSTEM IN C PROGRAMMING----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
// Structure that stores the customer details.
struct Customers
{
	int check_in, check_out, dos;
	char room_id[4], name[50], psp_ic_num[15], email[50], cont_num[15], booking_id[10];
};

//Structure that stores details of the available rooms
struct room_master
{
	char id[4], type[20];
	int price;
};

// Function to validate the rooms available currently and show them to user.
void rooms_validation(int ck_in, int ck_out)
{
	struct room_master room;
	struct Customers customer;
	int i;
	char is_room_available;
	/* Opening Rooms file in read mode and Availble Rooms file in write mode.*/
	FILE* f_r_rooms, * f_w_available_rooms;
	f_r_rooms = fopen("room_master.txt", "r");
	if (f_r_rooms == NULL)
	{
		printf("\nError!");
		exit(1);
	}

	f_w_available_rooms = fopen("available_rooms.txt", "w");
	if (f_w_available_rooms == NULL)
	{
		printf("\nError!");
		exit(1);
	}
	printf("\n The below table represents the rooms available currently.\n");
	printf("\n ROOM ID--ROOM TYPE--ROOM PRICE PER DAY\n");
	while (fread(&room, sizeof(struct room_master), 1, f_r_rooms)) // Reading each room details one by one.
	{
		is_room_available = 'Y';
		/* Opening Reserved Rooms File in read mode.*/
		FILE* f_read;
		f_read = fopen("reserved_rooms_data.txt", "r");
		if (f_read == NULL)
		{
			printf("Error!");
			exit(1);
		}
		while (fread(&customer, sizeof(struct Customers), 1, f_read)) // Reading each reserved rooms details one by one.
		{
			if (strcmp(room.id, customer.room_id) == 0) // If Room exists in reserved rooms.
			{
				for (i = ck_in; i < ck_out + 1; i++) // Iterating to check if a room is already reserved.
				{
					if (i >= customer.check_in && i < customer.check_out)
					{
						is_room_available = 'N';
						break;
					}
				}
			}
		}
		fclose(f_read); // Closing Reserved Rooms File..
		if (is_room_available == 'N')
		{
			continue;
		}
		// Printing the rooms available currently and adding them to available rooms file temprorarily.
		printf("     %s--%s--%d\n", room.id, room.type, room.price);
		fwrite(&room, sizeof(struct room_master), 1, f_w_available_rooms);
	}
	/* Closing Files..*/
	fclose(f_w_available_rooms);
	fclose(f_r_rooms);
}

//Function to update the customer data.
void updates()
{
	struct Customers customer;
	struct room_master room;
	char given_booking_id[8], valid_booking_id = 'N',upd_opt;
	int size;
	printf("\n----------------------------------------UPDATE BOOKED ROOM----------------------------------------\n");
	printf("\n Enter your Booking ID to update : ");  // Prompting user for their booking ID..
	while ((getchar()) != '\n'); // Clearing Input Buffer.
	scanf("%s", given_booking_id);

	/*Opening Reserved Rooms File in read mode and reading contents.*/
	FILE* f_read_write = fopen("reserved_rooms_data.txt", "r+");
	if (f_read_write == NULL)
	{
		printf("\n Error!");
		exit(1);
	}
	rewind(f_read_write);
	size = sizeof(struct Customers);
	while (fread(&customer, size, 1, f_read_write))
	{
		if (strcmp(given_booking_id, customer.booking_id) == 0) // Checking if Booking ID enteredand existing in particular record are same.
		{
			valid_booking_id = 'Y';
			/* Prompting user to select what he wants to update.*/
			printf("\n What do you want to update ?\n");
			printf("\n 1. Contact Number\n");
			printf("\n 2. Email\n");
			printf("\n 3. Booking Details\n");
			printf("\n 4. Exit\n");
			printf("\n Enter your selection (1...5) : ");
			scanf("%s", &upd_opt);

			if (upd_opt == '1')
			{
				/*Accepting users input and updating it in files by re-writing customers record.*/
				printf("\n Enter New Contact Number (Max. 11 Digits) : ");
				while ((getchar()) != '\n');
				scanf("%[^\n]s", customer.cont_num);
				/*Validating Contact Number..*/
				int i = 0, itisdigit = 1;
				while (customer.cont_num[i])
				{
					if (isdigit(customer.cont_num[i]) == 0)
					{
						itisdigit = 0;
					}
					i++;
				}
				if ((strlen(customer.cont_num) > 11) || (strlen(customer.cont_num) < 10) || (itisdigit == 0))
				{
					printf("ERROR: Invalid Mobile Number.");
					exit(0);
				}
				fseek(f_read_write, -size, SEEK_CUR);
				fwrite(&customer, sizeof(struct Customers), 1, f_read_write);
				printf("\n Your Contact Number has been updated...\n\n");
				exit(0);
			}
			else if (upd_opt == '2')
			{
				/*Accepting users input and updating it in files by re-writing customers record.*/
				printf("\n Enter New E-mail (Max. 50 Characters) : ");
				while ((getchar()) != '\n');
				scanf("%[^\n]s", customer.email);
				fseek(f_read_write, -size, SEEK_CUR);
				fwrite(&customer, sizeof(struct Customers), 1, f_read_write);
				printf("\n Your E-Mail has been updated...\n\n");
				exit(0);
			}
			else if (upd_opt == '3')
			{
				char checkout_opt[2], checkin_opt[2];
				//Prompting user to enter his choice of CHECK-IN and CHECK-OUT Days in character to update easily....
				printf("\n--------------------------------UPDATING BOOKED ROOM--------------------------------\n");
				printf("\n UPDATE CHECK-IN Day \n 1. Monday\n 2. Tuesday\n 3. Wednesday\n 4. Thursday\n 5. Friday\n 6. Saturday\n 7. Sunday\n Enter your preferred selection (1...7): ");
				scanf("%s", &checkin_opt[0]);
				switch (checkin_opt[0])
				{
				case '1': break;
				case '2': break;
				case '3': break;
				case '4': break;
				case '5': break;
				case '6': break;
				case '7': break;
				default: printf("\n ERROR : Invalid Selection. Please Try Again...\n");
					exit(0);
				}
				printf("\n UPDATE CHECK-OUT Day \n 1. Monday\n 2. Tuesday\n 3. Wednesday\n 4. Thursday\n 5. Friday\n 6. Saturday\n 7. Sunday\n Enter your preferred selection (1...7): ");
				scanf("%s", &checkout_opt[0]);
				switch (checkout_opt[0])
				{
				case '1': break;
				case '2': break;
				case '3': break;
				case '4': break;
				case '5': break;
				case '6': break;
				case '7': break;
				default: printf("\n ERROR : Invalid Selection. Please Try Again...\n");
					exit(0);
				}
				system("cls");
				/*Conversion of CHECK-IN and CHECK-OUT options to integers.*/
				customer.check_in = checkin_opt[0] - '0';
				customer.check_out = checkout_opt[0] - '0';
				printf("\tCheck-In :%d\tCheck-Out: %d\t", customer.check_in, customer.check_out);// Printing CHECK-IN and CHECK-OUT Days...
				/*Calculating Days Of Stay and printing them including validations..*/
				customer.dos = customer.check_out - customer.check_in;
				if (customer.dos >= 0)
					printf("Days of Stay : %d\n", customer.dos);
				else
				{
					printf("\n ERROR: Enter valid check in and check out dates. Pleade Try Again\n");
					exit(0);
				}

				rooms_validation(customer.check_in, customer.check_out); // Displaying the current available rooms of the hotel to customer and validation

				printf("\n Enter the Room ID you would like to reserve : "); // Prompting user to enter his choice of Room through Room ID.
				scanf("%s", &customer.room_id);

				char valid_room_id = 'N';
				// Opening available rooms file to vlaidate entered room id.
				FILE* f_r_available_rooms = fopen("available_rooms.txt", "r");
				if (f_r_available_rooms == NULL)
				{
					printf("\n Error!");
					exit(1);
				}
				while (fread(&room, sizeof(struct room_master), 1, f_r_available_rooms)) // Reading each room detail to check one by one.
				{
					if (strcmp(customer.room_id, room.id) == 0)
					{
						valid_room_id = 'Y'; // Making a Flag variable to validate easily
					}
				}
				fclose(f_r_available_rooms);
				if (valid_room_id == 'N')
				{
					printf("\n ERROR : Invalid Room ID entered. Please Try Again.\n");
					exit(0);
				}
				//Making Updates of Room Booking in files by re - writing customers record.* /
				fseek(f_read_write, -size, SEEK_CUR);
				fwrite(&customer, sizeof(struct Customers), 1, f_read_write);
				printf("\n Your Room Details have been updated.....\n\n");
				exit(0);
			}
			else if (upd_opt == '4')
			{
				//Exiting to Homepage..
				exit(0);
			}
			else
			{
				printf("Invalid Input\nPress any key to try again.");
				_getch();
				system("cls");
			}
		}
	}
	fclose(f_read_write); // Closing File..
	if (valid_booking_id == 'N')
		printf("\n ERROR : Invalid Booking ID entered. Please Try Again.\n");
	printf("\n Press any key to go back to HOMEPAGE....");
	_getch();
	system("cls");
}

//Function to create the Rooms master file.
void rooms()
{
	/* Assigning the Room id , Room type and room price to the structure.*/
	struct room_master room1 = {"101","Superior",180};
	struct room_master room2 = {"102","Deluxe",200};
	struct room_master room3 = {"103","Studio",250};
	struct room_master room4 = {"104","Executive Suite",400};
	struct room_master room5 = {"105","Deluxe Suite",500};
	struct room_master room6 = {"201","Superior",180};
	struct room_master room7 = {"202","Deluxe",200};
	struct room_master room8 = {"203","Studio",250};
	struct room_master room9 = {"204","Executive Suite",400};
	struct room_master room10 = {"205","Deluxe Suite",500};

	/* Opening Room File in write mode to write the room data in it.*/
	FILE* f_w_rooms;
	// open file for writing
	f_w_rooms = fopen("room_master.txt", "w");
	if (f_w_rooms == NULL)
	{
		printf("Error!");
		exit(1);
	}
	// Writing all rooms Data.
	fwrite(&room1, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room2, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room3, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room4, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room5, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room6, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room7, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room8, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room9, sizeof(struct room_master), 1, f_w_rooms);
	fwrite(&room10, sizeof(struct room_master), 1, f_w_rooms);

	fclose(f_w_rooms); // Closing File.
}

//Function to generate a recipt for the room booked.
void receipts()
{
	struct Customers customer;
	struct room_master room;
	char given_booking_id[8], valid_booking_id='N';
	int total_charges;
	printf("\n --------------------------------RECEIPTS--------------------------------\n");
	printf("\n Enter your Booking ID for receipt : "); // Prompting user for their booking ID..
	while ((getchar()) != '\n'); // Clearing Input Buffer.
	scanf("%s", given_booking_id);
	 
	/*Opening Reserved Rooms File in read mode and reading contents.*/
	FILE* f_read = fopen("reserved_rooms_data.txt", "r");
	if (f_read == NULL)
	{
		printf("\n Error!");
		exit(1);
	}
	while (fread(&customer, sizeof(struct Customers), 1, f_read))
	{
		if (strcmp(given_booking_id, customer.booking_id) == 0) // Checking if Booking ID entered and existing in particular record are same.
		{
			// Printing booking details of the customer..
			valid_booking_id = 'Y';
			printf("\n-------------------YOUR RECEIPT-------------------\n");
			printf("\n Name : %s\n", customer.name);
			printf("\n Passport/Ic Number : %s\n", customer.psp_ic_num);
			printf("\n Contact Number : %s\n", customer.cont_num);
			printf("\n E-Mail : %s\n\n", customer.email);
			printf("\n-------ROOM DETAILS-------\n");
			printf("\n Room-ID : %s\n", customer.room_id);
			printf("\n Check-In : %d\n", customer.check_in);
			printf("\n Check-Out : %d\n", customer.check_out);
			printf("\n Days of Stay : %d\n", customer.dos);
			/*Opening Rooms File to find room price, if customers room id and room id in room file tally.*/
			FILE* f_r_rooms;
			f_r_rooms = fopen("room_master.txt", "r");
			if (f_r_rooms == NULL)
			{
				printf("\n Error!");
				exit(1);
			}
			// Read Rooms file contents till end of file..
			while (fread(&room, sizeof(struct room_master), 1, f_r_rooms))
			{
				if (strcmp(customer.room_id, room.id) == 0) // Checking if the available room id and customers room id tally.
				{
					/* Calculating Total charges and printing them..*/
					printf("\n Room Type :%s\n", room.type);
					total_charges = customer.dos * (10 + room.price * 11 / 10);
					printf("\n----------TOTAL CHARGE----------\n");
					printf("\n Total Charges including taxes : RM %d/-\n", total_charges);
				}
			}
			fclose(f_r_rooms); // Closing Rooms File.
		}
	}
	fclose(f_read); // Closing Reserved Customers File.
	if (valid_booking_id == 'N')
		printf("\n ERROR : Invalid Booking ID entered. Please Try Again.\n");
	printf("\n Press any key to go back to HOMEPAGE....");
	_getch();
	system("cls"); // To Clear Screen..
}

//Function to accesss details of booked room.
void search_bookings()
{
	struct Customers customer;
	char given_booking_id[8],valid_booking_id = 'N';
	printf("\n --------------------------------SEARCH BOOKING DETAILS--------------------------------\n");
	printf("\n Enter your Booking ID : "); // Prompting user for their booking ID..
	while ((getchar()) != '\n'); // Clearing Input Buffer.
	scanf("%s", given_booking_id);

	/*Opening Reserved Rooms File in read mode and reading contents.*/
	FILE* f_read = fopen("reserved_rooms_data.txt", "r");
	if (f_read == NULL)
	{
		printf("\nError!");
		exit(1);
	}
	while (fread(&customer, sizeof(struct Customers), 1, f_read))
	{
		if (strcmp(given_booking_id,customer.booking_id)==0) // Checking if Booking ID entered and existing in particular record are same.
		{
			// Printing booking details of the customer..
			valid_booking_id = 'Y';
			printf("\n -----------------------YOUR BOOKING DETAILS-----------------------\n");
			printf("\n Name : %s\n", customer.name);
			printf("\n Passport/Ic Number : %s\n", customer.psp_ic_num);
			printf("\n Contact Number : %s\n", customer.cont_num);
			printf("\n E-Mail : %s\n\n", customer.email);
			printf("\n-------ROOM DETAILS-------\n");
			printf("\n Room-ID : %s\n", customer.room_id);
			printf("\n Check-In : %d\n",customer.check_in);
			printf("\n Check-Out : %d\n", customer.check_out);
			printf("\n Days of Stay : %d\n", customer.dos);
		}
	}
	fclose(f_read); // Closing File/
	if (valid_booking_id == 'N')
		printf("\n ERROR : Invalid Booking ID entered. Please Try Again.\n");
	printf("\n Press any key to go back to HOMEPAGE....");
	_getch();
	system("cls");
}

//Function to book a Hotel Room.
void room_booking()
{
	struct Customers customer;
	struct room_master room;
	int id;
	char checkout_opt[2], checkin_opt[2];

	//Prompting user to enter his choice of CHECK-IN and CHECK-OUT Days in character to validate easily....
	printf("\n--------------------------------ROOM BOOKING--------------------------------\n");
	printf("\n Please select CHECK-IN Day Option\n 1. Monday\n 2. Tuesday\n 3. Wednesday\n 4. Thursday\n 5. Friday\n 6. Saturday\n 7. Sunday\n Enter your preferred selection (1...7): ");
	scanf("%s", &checkin_opt[0]);
	switch (checkin_opt[0])
	{
	case '1': break;
	case '2': break;
	case '3': break;
	case '4': break;
	case '5': break;
	case '6': break;
	case '7': break;
	default: printf("\n ERROR : Invalid Selection. Please Try Again...\n");
		exit(0);
	}
	printf("\n Please select CHECK-OUT Day Option\n 1. Monday\n 2. Tuesday\n 3. Wednesday\n 4. Thursday\n 5. Friday\n 6. Saturday\n 7. Sunday\n Enter your preferred selection (1...7): ");
	scanf("%s", &checkout_opt[0]);
	switch (checkout_opt[0])
	{
	case '1': break;
	case '2': break;
	case '3': break;
	case '4': break;
	case '5': break;
	case '6': break;
	case '7': break;
	default: printf("\n ERROR : Invalid Selection. Please Try Again...\n");
		exit(0);
	}
	system("cls");
	/*Conversion of CHECK-IN and CHECK-OUT options to integers.*/
	customer.check_in = checkin_opt[0] - '0';
	customer.check_out = checkout_opt[0] - '0';
	printf("\tCheck-In :%d\tCheck-Out: %d\t", customer.check_in, customer.check_out);// Printing CHECK-IN and CHECK-OUT Days...
	/*Calculating Days Of Stay and printing them including validations..*/
	customer.dos = customer.check_out - customer.check_in;
	if (customer.dos >= 0)
		printf("Days of Stay : %d\n", customer.dos);
	else
	{
		printf("\n ERROR: Enter valid check in and check out dates. Pleade Try Again\n");
		exit(0);
	}
	rooms_validation(customer.check_in,customer.check_out);// Displaying the current available rooms of the hotel to customer and validation

	printf("\n Enter the Room-ID you would like to reserve : "); // Prompting for Customers choice of ROOM by receiving Room-ID.
	scanf("%s", &customer.room_id);

	//Room ID Validation Begins.

	char valid_room_id='N';
	FILE* f_r_available_rooms = fopen("available_rooms.txt","r"); //Opening avaialable_rooms.txt File in append mode.
	if (f_r_available_rooms == NULL)
	{
		printf("\n Error!");
		exit(1);
	}
	while (fread(&room, sizeof(struct room_master), 1, f_r_available_rooms)) // Iterating to check if Room-ID entered by customer is valid.
	{
		if (strcmp(customer.room_id,room.id) == 0)
		{
			valid_room_id = 'Y';
		}
	}
	fclose(f_r_available_rooms);
	if (valid_room_id == 'N')
	{
		printf("\n ERROR : Invalid Room ID entered. Please Try Again.\n");
		exit(0);
	}

	//Room ID Validation Ends....

	while ((getchar()) != '\n');//Clearing Input Buffer
	printf("\n Enter your Name(Max. 50 Characters) : "); // Prompting for Customers Name.
	scanf("%[^\n]s", &customer.name);

	printf("\n Enter passport/IC number (Max.15 Characters): ");// Prompting for Customers Passport Number.
	scanf("%s", &customer.psp_ic_num);

	printf("\n Enter your Mobile number (Max. 11 digits): ");// Prompting for Customers Mobile Number.
	scanf("%s", &customer.cont_num);

	//Contact Number validation begins..

	int i=0, itisdigit = 1;
	while (customer.cont_num[i]) // Iterating to check if each character in Contact NUmber is Digit.
	{
		if (isdigit(customer.cont_num[i]) == 0)
		{
			itisdigit = 0;
			printf("Y");
		}
		i++;
	}
	if ((strlen(customer.cont_num) > 11) || (strlen(customer.cont_num) < 10) || (itisdigit == 0))
	{
		printf("\n ERROR: Invalid Mobile Number.\n");
		exit(0);
	}

	//Contact Number Validation Ends....

	printf("\n Enter your E-mail (Max. 50 Characters): "); // Prompting for Customers E-Mail.
	scanf("%s", &customer.email);

	srand(time(0));
	id = rand(); // Generating Customers Booking ID.....
	_itoa(id, customer.booking_id, 10);

	FILE* f_reserved;
	f_reserved = fopen("reserved_rooms_data.txt", "a"); //Opening reserved_rooms.txt File in append mode.
	if (f_reserved == NULL)
	{
		printf("Error!");
		exit(1);
	}
	fwrite(&customer, sizeof(struct Customers), 1, f_reserved); // Writing Customer Data in Structure into reserved_rooms.txt File..
	fclose(f_reserved); //Closing reserved_rooms.txt file.
	printf("\n Congrats!!! Your reservation has been confirmed !\n");
	printf("\n Your Booking ID is %s \n", customer.booking_id);// Displaying Customers ID for reference
	printf(" (NOTE : Booking ID is important. Kindly Remember or note it down.)\n");// Displaying Customers ID for reference
	printf("\n Press any key to return to HOMEPAGE");
	_getch();
	system("cls");
}

//Function to access the details of Hotel Rooms.
void disp_all_rooms()
{
	rooms();
	struct room_master room;
	FILE* f_r_rooms;
	// Opening Rooms Files in read mode.
	f_r_rooms = fopen("room_master.txt", "r");
	if (f_r_rooms == NULL)
	{
		printf("Error!");
		exit(1);
	}
	// read Rooms file contents till end of file and printing them
	printf("\n------------------------------------ROOMS AND PRICES------------------------------------\n");
	printf("\n ROOMID---ROOM TYPE--ROOM PRICE\n");
	while (fread(&room, sizeof(struct room_master), 1, f_r_rooms))
		printf("\n   %s----%s--%d\n", room.id,room.type, room.price);

	// close file
	fclose(f_r_rooms);

	printf("\n You can book Rooms by selecting option '2' in HOMEPAGE\n");
	printf("\n Press any key to return to HOMEPAGE");
	_getch();
	system("cls"); // To clear screen.
}

//Creating a function to access the homepage in the Hotel Booking System
void home_page()
{
	char opt;
	while (1)
	{	//Providing the menu options and accepting user input.
		printf("\n  -----------HOTEL ROOM BOOKING SYSTEM-----------\n\n");
		printf("\t  ---------HOME PAGE---------\n\n");
		printf("  1. Room Types and Prices\n");
		printf("\n  2. Book Room\n");
		printf("\n  3. Search Booking details\n");
		printf("\n  4. Update Booking details\n");
		printf("\n  5. View Receipt\n");
		printf("\n  6. Exit\n");
		printf("\n  Enter your option (1...6) : ");
		scanf("%s", &opt);
		system("cls");
		//Checking user input and providing the corresponding details respectively.
		if (opt == '1') {
			disp_all_rooms();
		}
		else if (opt == '2') {
			room_booking();
		}
		else if (opt == '3') {
			search_bookings();
		}
		else if (opt == '4') {
			updates();
		}
		else if (opt == '5') {
			receipts();
		}
		else if (opt == '6') {
			printf("Thank You ...");
			exit(0);
		}
		else
		{
			printf("Invalid Input\nPress any key to try again.");
			_getch();
			system("cls");
		}
	}
}

// Initiation Code
int main()
{
	home_page();  //Calling Homepage function
	return 0;
}
