#! /usr/bin/python
import sys
sys.path.append("build/protos")
import addressbook_pb2
from time import time
from addressbook_pb2 import google_dot_protobuf_dot_timestamp__pb2 as timestamp

try:
  raw_input          # Python 2
except NameError:
  raw_input = input  # Python 3


# This function fills in a Person message based on user input.
def PromptForAddress(person):
  person.id = int(raw_input("Enter person ID number: "))
  person.name = raw_input("Enter name: ")

  email = raw_input("Enter email address (blank for none): ")
  if email != "":
    person.email = email

  while True:
    number = raw_input("Enter a phone number (or leave blank to finish): ")
    if number == "":
      break

    phone_number = person.phones.add()
    phone_number.number = number

    type = raw_input("Is this a mobile, home, or work phone? ")
    if type == "mobile":
      phone_number.type = addressbook_pb2.Person.MOBILE
    elif type == "home":
      phone_number.type = addressbook_pb2.Person.HOME
    elif type == "work":
      phone_number.type = addressbook_pb2.Person.WORK
    else:
      print("Unknown phone type; leaving as default value.")

    person.last_updated.CopyFrom(timestamp.Timestamp(seconds=int(time())))


# Main procedure:  Reads the entire address book from a file,
#   adds one person based on user input, then writes it back out to the same
#   file.
if len(sys.argv) != 2:
  print("Usage:", sys.argv[0], "ADDRESS_BOOK_FILE")
  sys.exit(-1)

address_book = addressbook_pb2.AddressBook()

# Read the existing address book.
try:
  with open(sys.argv[1], "rb") as f:
    address_book.ParseFromString(f.read())
except IOError:
  print(sys.argv[1] + ": File not found.  Creating a new file.")

# Add an address.
while True:
    print("Add person to address book? yes | no")
    choice = raw_input()
    if choice != "yes" and choice != "no":
        print("Please enter yes or no.")
        continue
    if choice == "no":
        break
    PromptForAddress(address_book.people.add())

# Write the new address book back to disk.
with open(sys.argv[1], "wb") as f:
  f.write(address_book.SerializeToString())