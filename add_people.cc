#include <ctime>
#include <fstream>
#include <google/protobuf/util/time_util.h>
#include <iostream>
#include <string>

#include "addressbook.pb.h"

using namespace std;

using google::protobuf::util::TimeUtil;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
    cout << "Enter person ID number: " << endl;
    int id;
    cin >> id;
    person->set_id(id);
    // Ignore delimeter
    // ignores first 256 characters or all the character until it encounters delimeter (here \n in your case), 
    // whichever comes first (here \n is the first character, so it ignores until \n is encountered).
    cin.ignore(256, '\n');

    cout << "Enter name: " << endl;
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): " << endl;
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    // Add multiple phone numbers
    while (true) {
        cout << "Enter a phone number (or leave blank to finish): " << endl;
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        //Because "repeated PhoneNumber phones", we have "add" prefix.
        tutorial::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? mobile | home | work " << endl;
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        } 
        else if (type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        } 
        else if (type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        } 
        else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
    *person->mutable_last_updated() = TimeUtil::SecondsToTimestamp(time(NULL));
}

// Main function:  Reads the entire address book from a file,
// add people based on user input, then writes it back out to the same file.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    // https://github.com/protocolbuffers/protobuf/blob/master/src/google/protobuf/stubs/common.h#L116
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        // Read the existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << ": File not found.  Creating a new file." << endl;
        } 
        else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Keep adding address until user say no.
    while (true)
    {
        cout << "Add person to address book? yes | no" << endl;
        string choice;
        getline(cin, choice);
        if ((choice != "yes") && (choice != "no")) {
            cout << "Please enter yes or no." << endl;
            continue;
        }
        if (choice == "no") {
            break;
        } 
        else {
            PromptForAddress(address_book.add_people());
        }
    }


    {
        // Write the new address book back to disk.
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write address book." << endl;
            return -1;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
