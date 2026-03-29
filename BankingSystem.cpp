#include<iostream>
#include<string>
#include<vector>
using namespace std;

// BASE CLASS
class account{
    public:
    string name;
    long int id;

    account(string name, long int id){
        this->name = name;
        this->id = id;
    }
    void display(){
        cout<<"ACCOUNT HOLDER NAME: "<<name<<endl;
        cout<<"ACCOUNT ID: "<<id<<endl;
        cout<<"-----------------"<<endl;
    }
};

// MEMBER CLASS INHERITING ACCOUNT CLASS, HEIRARCHICAL INHERITANCE WITH ACCOUNT CLASS
class member : public account {
    private: // ENCAPSULATION OF PASSWORD DATA MEMBER
    string password;
    public:
    long long int balance;

    // CONSTRUCTOR TO INITIALIZE THE MEMBER OBJECT WITH NAME, ID, PASSWORD AND BALANCE
    member(string name, long int id, string password, long long int balance) : account(name, id) {
        this->password = password;
        this->balance = balance;
    }
    string get_password() const { // GETTER FUNCTION TO ACCESS THE PRIVATE PASSWORD DATA MEMBER
        return password;
    }
    string display_password() const { // FUNCTION TO DISPLAY PASSWORD IN ENCRYPTED FORM FOR SECURITY REASONS
        return password;
    }
    void set_password(string new_password){
    password = new_password;
}
    // FUNCTION TO DISPLAY MEMBER DETAILS, EXCLUDING PASSWORD FOR SECURITY REASONS
    void display() {
        cout << "MEMBER NAME: " << name << endl;
        cout << "MEMBER ID: " << id << endl;
        cout<<"MEMBER PASSWORD: ENCRYPTED"<<endl;
        cout<<"MEMBER BALANCE: "<<balance<<endl;
        cout << "-----------------" << endl;
    }
};
// ADMIN CLASS INHERITING ACCOUNT CLASS, HIERARCHICAL INHERITANCE WITH ACCOUNT CLASS
class admin : public account { 
    
    public:

    admin(string name, long int id) : account(name, id) { // CONSTRUCTOR TO INTIALIZE THE ADMIN OBJECT WITH NAME AND ID AND INHERIT THE NAME AND ID FROM ACCOUNT CLASS
    }
    
    void display() {
        cout << "ADMIN NAME: " << name << endl;
        cout << "ADMIN ID: " << id << endl;
        cout << "-----------------" << endl;
    }
};
// LOAN CLASS TO HANDLE LOAN APPLICATIONS
class Loan {
public:
    string name;
    long int id;
    string password;
    long long int amount;

    Loan(string name, long int id, long long int amount){
        this->name = name;
        this->id = id;
        this->amount = amount;

    }
    void display() {
        cout << "Loan Applicant: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Requested Loan Amount: " << amount << endl;
    }
};
// TRANSACTION CLASS TO HANDLE TRANSACTION DETAILS AND HISTORY
class transaction{
    public:
    long int sender_id;
    long int receiver_id;
    string sender_name;
    string receiver_name;
    long long int amount;

    transaction(long int sender_id, long int receiver_id, string sender_name, string receiver_name, long long int amount){
        this->sender_id = sender_id;
        this->receiver_id = receiver_id;
        this->sender_name = sender_name;
        this->receiver_name = receiver_name;
        this->amount = amount;
    }
    void display_transaction(){
        cout<<"SENDER NAME: "<<sender_name<<endl;
        cout<<"SENDER ID: "<<sender_id<<endl;
        cout<<"RECEIVER NAME: "<<receiver_name<<endl;
        cout<<"RECEIVER ID: "<<receiver_id<<endl;
        cout<<"AMOUNT TRANSFERRED: "<<amount<<endl;
        cout<<"-------------------------"<<endl;
    }
};
// BANK CLASS TO MANAGE ALL THE OPERATIONS OF THE BANKING SYSTEM, AGGREGATION OF MEMBER, ADMIN, LOAN AND TRANSACTION CLASSES
class bank {
public:
    // VECTORS TO HANDLE DATABASE:
    vector<member> member_acc;
    vector<admin> admin_acc;
    vector<Loan> loan_applications;
    vector<transaction> transaction_history;

    // POINTER TO TRACK THE LOGGED IN MEMBER FOR MEMBER-SPECIFIC OPERATIONS
    member* loggedInMember = nullptr;

    // FUNCTIONS TO MANAGE THE BANKING SYSTEM OPERATIONS:
    void add_member(string name, long int id, string password, long long int balance) {
        member_acc.push_back(member(name, id, password, balance));
    }
    // FUNCTION TO ADD ADMIN LOGIN CREDENTIALS TO ADMIN VECTOR DATABASE
    void add_admin(string name, long int id) {
        admin_acc.push_back(admin(name, id));
    }
    // HANDLES ADMIN LOGIN BY VERIFYING THE ENTERED ID WITH THE ADMIN VECTOR DATABASE, ALLOWS MAXIMUM 3 ATTEMPTS FOR LOGIN
    bool admin_login(){
        long int id;
        cout<<"PLEASE ENTER YOUR FOUR DIGIT ACCESS CODE: ";
        for(int i=1; i<=3; i++){
            cin>>id;
            for(admin &a : admin_acc){
                if(a.id==id){
                cout<<"ACCESS CODE VERIFIED!!!"<<endl;
                cout<<"\n\033[1mWELCOME "<<a.name<<"\033[0m"<<endl;
                cout<<"------------------------------"<<endl;
                return true;
                }

            }
            cout<<"ACCESS CODE INVALID!!! PLEASE TRY AGAIN: ";
            
            if(i==3){
                cout<<"MAXIMUM ATTEMPTS REACHED!!! LOGIN ID FAILED!!!";
                exit(0);
            }
        }
        return false;
    }
    // HANDLES MEMBER LOGIN BY VERIFYING THE ENTERED ID AND PASSWORD WITH THE MEMBER VECTOR DATABASE, ALLOWS MAXIMUM 3 ATTEMPTS FOR LOGIN, SETS THE LOGGED IN MEMBER POINTER TO THE SUCCESSFULLY LOGGED IN MEMBER FOR MEMBER-SPECIFIC OPERATIONS
    bool member_login() {
    long int id;
    string password;
    cout << "PLEASE ENTER YOUR ACCOUNT ID: ";
    cin >> id;
    bool memberid = false;
    for(member &m : member_acc){
        if(m.id == id){
            memberid = true;
            break;
        }
    }
    if(memberid != true){
        cout<<"MEMBER ID DOES NOT EXISTS IN THE DATABASE, ACCOUNT LOGIN FAILED!!!"<<endl;
        exit(0);
    }
    cin.ignore(); // clear newline left by cin >>
    for (int i = 1; i <= 3; i++) {
        cout << "PLEASE ENTER YOUR PASSWORD: ";
        getline(cin, password); //USED GETLINE FUNCTION TO TAKE STRING INPUT WITH SPACES
        for (member &m : member_acc) { //FOR LOOP FOR VECTOR TO LOOP THROUGH MEMBER ACCOUNTS TO VERIFY CREDENTIALS
            if (m.id == id && m.get_password() == password) {
                cout << "LOGIN SUCCESSFUL!!!" << endl;
                cout << "\n\033[1mWELCOME " << m.name <<"\033[0m\n"<<endl;
                cout<<"--------------------------\n"<<endl;
                loggedInMember = &m; // SET THE LOGGED IN MEMBER
                return true;
            }
        }
        if (i < 3) {
            cout << "INVALID CREDENTIALS!!! PLEASE TRY AGAIN." << endl;
        } else {
            cout << "MAXIMUM ATTEMPTS REACHED!!! LOGIN FAILED!!!" << endl;
            exit(0);
        }
    }
    return false;
}
    // FUNCTION TO DELETE MEMBER ACCOUNT BY VERIFICATION OF ACCOUNT ID
    bool delete_member_acc(){
        long int id;
        cout<<"PLEASE ENTER THE ID OF THE ACCOUNT TO BE DELETED: ";
        cin>>id;
        for(size_t i=0; i<member_acc.size(); i++){ //USED SIZE_T FOR FOR UNSIGNED INTEGER TO AVOID SIGNED-UNSIGNED COMPARISON WARNING
            if(member_acc[i].id == id){
                cout<<"ACCOUNT FOUND WITH FOLLOWING CREDENTIALS: "<<endl;
                member_acc[i].display();
                cout<<"THE ABOVE ACCOUNT WILL BE DELETED!!!"<<endl;
                member_acc.erase(member_acc.begin() + i);
                cout<<"ACCOUNT DELETED SUCCESSFULLY!!!"<<endl;
                return true;
            }
        }
        cout<<"ACCOUNT NOT FOUND!!! DELETE FAILED!!!"<<endl;
        return false;
}
    // FUNCTION TO DISPLAY ALL MEMBER ACCOUNTS
    void display_all_member_accounts(){
        cout<<"ALL MEMBER ACCOUNTS: "<<endl;
        for(member &m : member_acc){
            m.display();
        }
}
    // FUNCTION TO DISPLAY ALL ADMIN ACCOUNTS
    void display_all_admin_accounts(){
        cout<<"ALL ADMIN ACCOUNTS: "<<endl;
        for(admin &a : admin_acc){
            a.display();
        }
}
    // FUNCTION TO SEARCH ACCOUNT BY ID AND DISPLAY THE ACCOUNT DETAILS IF FOUND
    bool search_account_by_id(long int id){
        for(member &m : member_acc){
            if(m.id==id){
                cout<<"MEMBER ACCOUNT EXISTS HAVING FOLLOWING CREDENTIALS: \n"<<endl;
                m.display();
                return true;
            }
        }
        cout<<"NO MEMBER ACCOUNT EXISTS WITH THE ENTERED ID!!!"<<endl;
        return false;
}
    // FUNCTION TO CONVERT LOWERCASE CHARACTERS TO UPPERCASE
        string toUppercase(string s){
        for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] >= 97 && s[i] <= 122) {
            s[i]  = s[i] - 32; // SUBTRACTING 32 FROM ASCII VALUE OF LOWERCASE LETTER TO CONVERT IT TO UPPERCASE
        }
    }
    return s;
}
    bool search_account_by_name(string name){
        name = toUppercase(name);
        for(member &m : member_acc){
            if(m.name==name){
                cout<<"THE FOLLOWING ACCOUNT EXISTS WITH FOLLOWING CREDENTIALS: "<<endl;
                m.display();
                return true;
            }
        }
        cout<<"THE FOLLOWING ACCOUNT DOES NOT EXISTS!!!";
        return false;
}
    // FUNCTION TO UPDATE MEMBER DETAILS, ALLOWS TO UPDATE NAME AND PASSWORD
    bool update_member_details(){
        long int id;
        int choice;
        string name;
        string password;
        char confirm;
        cout<<"ENTER THE ACCOUNT ID FOR UPDATION OF MEMBER DETAILS: ";
        cin>>id;
        for(member &m : member_acc){
            if(m.id==id){
                cout<<"MEMBER ID FOUND WITH FOLLOWING CREDENTIALS: "<<endl;
                m.display();
                cout<<"PLEASE SELECT THE DETAIL TO BE UPDATED: "<<endl;
                cout<<"1. NAME \n2. PASSWORD"<<endl;
                cin>>choice;
                switch(choice){
                    case 1:
                    cout<<"ENTER THE NEW NAME FOR THE ACCOUNT HOLDER: ";
                    cin.ignore();
                    getline(cin, name);
                    name = toUppercase(name);
                    cout<<"ARE U SURE TO CHANGE THE NAME FROM "<<m.name<<" TO "<<name<<" ? (Y/N): ";
                    cin>>confirm;
                    if(confirm=='Y' || confirm=='y'){
                        m.name = name;
                        cout<<"NAME UPDATED SUCCESSFULLY WITH UPDATED CREDENTIALS ARE: "<<endl;
                        m.display();
                    }
                    else{
                        cout<<"NAME UPDATE CANCELLED!!!"<<endl;
                    }
                    break;
                    case 2:
                    cout<<"PLEASE ENTER YOUR CURRENT PASSWORD: ";
                    cin>>password;
                    if(m.get_password()==password){
                        cout<<"PASSWORD VERIFIED!!!"<<endl;
                        cout<<"PLEASE ENTER THE NEW PASSWORD: ";
                        cin.ignore();
                        getline(cin, password);
                        cout<<"ARE U SURE TO CHANGE THE PASSWORD? (Y/N): ";
                        cin>>confirm;
                        if(confirm=='Y' || confirm=='y'){
                            m.set_password(password);
                            cout<<"PASSWORD UPDATED SUCCESSFULLY "<<endl;
                        }
                        else{
                            cout<<"PASSWORD UPDATE CANCELLED!!!"<<endl;
                        }
                    }
                    else{
                        cout<<"CURRENT PASSWORD INVALID!!! PASSWORD UPDATE FAILED!!!"<<endl;
                    }
                }
                return true;
            }
        }
        cout<<"NO MEMBER ACCOUNT EXISTS WITH THE ENTERED ID!!! UPDATE FAILED!!!"<<endl;
        return false;
}
    // FUNCTION TO DISPLAY MEMBER PASSWORD, BY VERIFICATION OF ACCOUNT ID, FOR ADMIN USE ONLY
    bool member_password(){
        long int id;
        cout<<"PLEASE ENTER THE ACCOUNT ID TO CHECK PASSWORD: ";
        cin>>id;
        for(member &m : member_acc){
            if(m.id==id){
                cout<<"MEMBER ACCOUNT FOUND!! "<<endl;
                cout<<"MEMBER NAME: "<<m.name<<endl;
                cout<<"PASSWORD: "<<m.display_password()<<endl;
                return true;
            }
        }
        return false;
}
    // FUNCTION TO APPLY FOR LOAN, POINTER SAVES THE LOGGED IN MEMBER DETAILS TO USE IN LOAN APPLICATION AND STORE THE DETAILS IN THE VECTOR DATABASE OF LOAN APPLICATIONS
    void apply_loan() {
    if (loggedInMember == nullptr) {
        cout << "ERROR: No member is currently logged in!" << endl;
        return;
    }
    long long int amount;
    cout << "ENTER THE AMOUNT FOR THE LOAN APPLICATION: ";
    cin >> amount;

    // Use logged-in member’s details directly
    loan_applications.push_back(
        Loan(loggedInMember->name, loggedInMember->id, amount)
    );
    cout << "LOAN APPLICATION SUCCESSFULLY GENERATED FOR " 
         << loggedInMember->name << "!!!" << endl;
}
    // FUNCTION TO APPROVE LOAN APPLICATION
    bool approve_loan_application() {
    long int id;
    cout << "PLEASE ENTER THE MEMBER ID FOR LOAN APPROVAL: ";
    cin >> id;

    for (size_t i = 0; i < loan_applications.size(); i++) {
        if (loan_applications[i].id == id) {
            cout << "LOAN APPLICATION FOUND: " << endl;
            for (member &m : member_acc) {
                if (m.id == id) {
                    m.balance += loan_applications[i].amount;
                    cout << "LOAN APPROVED!!! BALANCE UPDATED." << endl;
                    loan_applications.erase(loan_applications.begin() + i);
                    return true;
                }
            }
        }
    }
    cout<<"ACCOUNT ID DOES NOT EXIST FOR LOAN APPLICATION APPROVAL, HENCE PROCESS FAILED"<<endl;
    return false;
}
    // FUNCTION TO REJECT LOAN APPLICATION
    bool reject_loan_application() {
    long int id;
    cout << "PLEASE ENTER THE MEMBER ID FOR LOAN REJECTION: ";
    cin >> id;

    for (size_t i = 0; i < loan_applications.size(); i++) { //USED SIZE_T FOR FOR UNSIGNED INTEGER TO AVOID SIGNED-UNSIGNED COMPARISON WARNING
        if (loan_applications[i].id == id) {
            cout << "LOAN APPLICATION FOUND: " << endl;
            loan_applications[i].display();
            cout << "LOAN APPLICATION REJECTED!!!" << endl;
            loan_applications.erase(loan_applications.begin() + i);
            return true;
        }
    }
    cout << "ACCOUNT ID DOES NOT EXIST FOR LOAN APPLICATION APPROVAL, HENCE PROCESS FAILED" << endl;
    return false;
}
    // FUNCTION TO DISPLAY ALL LOAN APPLICATIONS, FOR ADMIN USE ONLY
    void display_all_loan_applications() {
    cout << "ALL LOAN APPLICATIONS: " << endl;
    for (Loan &l : loan_applications){
        if(loan_applications.empty()){
            cout<<"NO PENDING LOAN APPLICATIONS"<<endl;
        }
        l.display();
    }
}
    // FUNCTION TO MANAGE LOAN APPLICATIONS, ALLOWS ADMIN TO APPROVE OR REJECT LOAN APPLICATIONS
    void manage_loan_application() {
        display_all_loan_applications();
        if(loan_applications.empty()){
            cout<<"NO LOAN APPLICATIONS TO MANAGE!!!"<<endl;
            return;
        }
        cout<<"1. APPROVE LOAN APPLICATION \n2. REJECT LOAN APPLICATION"<<endl;
        int choice;
        cout<<"PLEASE SELECT THE OPERATION TO BE PERFORMED: ";
        cin>>choice;
        switch(choice){
            case 1:
            approve_loan_application();
            break;
            case 2:
            reject_loan_application();
            break;
            default:
            cout<<"INVALID OPTION SELECTED!!! PLEASE TRY AGAIN!!!"<<endl;
        }
}
    // FUNCTION TO ASK USER IF THEY WISH TO CONTINUE USING THE PORTAL SERVICES AFTER COMPLETION OF AN OPERATION, RETURNS TRUE FOR CONTINUATION AND FALSE FOR EXITING THE PORTAL
    bool looping_system(){
        int choice;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"DO U WISH TO CONTINUE THE FUNCTIONS IN PORTAL: "<<endl;
        cout<<"1. YES"<<endl;
        cout<<"2. NO"<<endl;
        cout<<"PLEASE CHOOSE YOUR OPTION: ";
        cin>>choice;
        if(choice==1){
            cout<<"YOU HAVE CONFIRMED CONTINUATION OF PORTAL SERVICES!!! "<<endl;
            cout<<"--------------------------------------------------"<<endl;
            return true;
        } else if(choice==2){
            cout<<"THANKS FOR USING THE BANK MANAGEMENT SYSTEM!!! LOGGING OUT!!!"<<endl;
            exit(0);
        }
        else{
            cout<<"INVALID OPTION SELECTED!!! PLEASE TRY AGAIN!!!"<<endl;
            return looping_system();
        }
}
    bool view_account_details() {
        if (loggedInMember == nullptr) {
            cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
            return false;
        }
        cout << "ACCOUNT DETAILS FOR " << loggedInMember->name << ": " << endl;
        loggedInMember->display();
        return true;
}
    bool view_loan_status(){
        if(loggedInMember==nullptr){
            cout<<"ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!"<<endl;
            return false;
        }
        cout<<"LOAN APPLICATION STATUS FOR "<<loggedInMember->name<<": "<<endl;
        for (Loan &l : loan_applications) {
            if (l.id == loggedInMember->id ) {
            cout << "LOAN APPLICATION PENDING WITH FOLLOWING DETAILS: " << endl;
            l.display();
            return true;
        }
    }

    cout << "NO PENDING LOAN APPLICATIONS FOUND FOR THE CURRENT LOGGED IN MEMBER ACCOUNT: "<<loggedInMember->name<< endl;
    return false;
}
    bool deposit_money() {
    if (loggedInMember == nullptr) {
        cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
        return false;
    }

    long long int amount;
    cout << "ENTER THE AMOUNT TO DEPOSIT: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "INVALID AMOUNT ENTERED!!!" << endl;
        return false;
    }

    loggedInMember->balance += amount;
    transaction_history.push_back(transaction(loggedInMember->id, 0, loggedInMember->name, "CASH DEPOSIT", amount));

    cout << "AMOUNT DEPOSITED SUCCESSFULLY!!!" << endl;
    cout << "UPDATED BALANCE: " << loggedInMember->balance << endl;

    return true;
}
    bool withdraw_money() {
    if (loggedInMember == nullptr) {
        cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
        return false;
    }

    long long int amount;
    cout << "ENTER THE AMOUNT TO WITHDRAW: ";
    cin >> amount;
    if (amount <= 0) {
        cout << "INVALID AMOUNT ENTERED!!!" << endl;
        return false;
    }

    if (amount > loggedInMember->balance) {
        cout << "INSUFFICIENT BALANCE!!! TRANSACTION FAILED!!!" << endl;
        return false;
    }

    loggedInMember->balance -= amount;
    transaction_history.push_back(transaction(loggedInMember->id, 0, loggedInMember->name, "CASH WITHDRAWAL", amount));

    cout << "AMOUNT WITHDRAWN SUCCESSFULLY!!!" << endl;
    cout << "UPDATED BALANCE: " << loggedInMember->balance << endl;

    return true;
}
    bool check_balance() {
    if (loggedInMember == nullptr) {
        cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
        return false;
    }

    cout << "CURRENT ACCOUNT BALANCE: " << loggedInMember->balance << endl;
    return true;
}
    bool transfer_money() {
    if (loggedInMember == nullptr) {
        cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
        return false;
    }

    long int receiver_id;
    long long int amount;

    cout << "ENTER RECEIVER ACCOUNT ID: ";
    cin >> receiver_id;

    if (receiver_id == loggedInMember->id) {
        cout << "YOU CANNOT TRANSFER MONEY TO YOUR OWN ACCOUNT!!!" << endl;
        return false;
    }

    member* receiver = nullptr;

    for (member &m : member_acc) {
        if (m.id == receiver_id) {
            receiver = &m;
            break;
        }
    }

    if (receiver == nullptr) {
        cout << "RECEIVER ACCOUNT NOT FOUND!!!" << endl;
        return false;
    }

    cout << "ENTER AMOUNT TO TRANSFER: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "INVALID AMOUNT ENTERED!!!" << endl;
        return false;
    }

    if (amount > loggedInMember->balance) {
        cout << "INSUFFICIENT BALANCE!!! TRANSACTION FAILED!!!" << endl;
        return false;
    }

    // Perform transfer
    loggedInMember->balance -= amount;
    receiver->balance += amount;
    // Record transaction
    transaction_history.push_back(transaction(loggedInMember->id, receiver->id, loggedInMember->name, receiver->name, amount));


    cout << "AMOUNT TRANSFERRED SUCCESSFULLY!!!" << endl;
    cout << "YOUR UPDATED BALANCE: " << loggedInMember->balance << endl;

    return true;
}
    bool change_member_password() {

    // Step 1: Check login
    if (loggedInMember == nullptr) {
        cout << "ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!" << endl;
        return false;
    }

    string current_password;
    string new_password;
    string confirm_password;

    cin.ignore();

    cout << "ENTER CURRENT PASSWORD: ";
    getline(cin, current_password);

    if (loggedInMember->get_password() != current_password) {
        cout << "INCORRECT CURRENT PASSWORD!!!" << endl;
        return false;
    }

    // Step 3: Enter new password
    cout << "ENTER NEW PASSWORD: ";
    getline(cin, new_password);

    cout << "CONFIRM NEW PASSWORD: ";
    getline(cin, confirm_password);

    if(loggedInMember->get_password() == new_password){
        cout<<"YOU HAVE ENETERED YOUR PREVIOUS ACCOUNT PASSWORD AS THE NEW ONE!! ACCOUNT UPDATION FAILED"<<endl;
        return false;
    }
    // Step 4: Match confirmation
    if (new_password != confirm_password) {
        cout << "PASSWORDS DO NOT MATCH!!!" << endl;
        return false;
    }
    // Step 5: Update password
    loggedInMember->set_password(new_password);

    cout << "PASSWORD CHANGED SUCCESSFULLY!!!" << endl;
    return true;
}
    bool view_transaction_history(){
        if(loggedInMember==nullptr){
            cout<<"ERROR: NO MEMBER IS CURRENTLY LOGGED IN!!!"<<endl;
            return false;
        }
        cout<<"TRANSACTION HISTORY FOR "<<loggedInMember->name<<": "<<endl;
        if(transaction_history.empty()){
            cout<<"NO TRANSACTIONS TO DISPLAY!!!"<<endl;
            return true;
        }
        for(transaction &t : transaction_history){
            if(t.sender_id == loggedInMember->id || t.receiver_id == loggedInMember->id){
                t.display_transaction();
            }
            
        }
        return true;
}
    void generate_report() {
        cout << "\nALL MEMBER ACCOUNTS: " << endl;
        cout<<"--------------------------\n"<<endl;
        for (member &m : member_acc) {
            m.display();
        }
        cout << "\nALL ADMIN ACCOUNTS: " << endl;
        cout<<"--------------------------\n"<<endl;
        for (admin &a : admin_acc) {
            a.display();
        }
        cout << "\nALL LOAN APPLICATIONS: " << endl;
        cout<<"--------------------------\n"<<endl;
        if(loan_applications.empty()){
            cout<<"NO PENDING LOAN APPLICATIONS FOR THIS BRANCH"<<endl;
        } else {
            for(Loan l : loan_applications){
                l.display();
            }
        }
        cout << "\nALL TRANSACTIONS: " << endl;
        cout<<"--------------------------\n"<<endl;
        if(transaction_history.empty()){
            cout<<"NO TRANSACTION HISTORY COULD BE GENERATED FOR THIS BRANCH"<<endl;
        } else {
            for(transaction t : transaction_history){
                t.display_transaction();
            }
        }
}
    void create_member_account() {
    string name, password;
    long int id;
    long long int balance;

    cout << "ENTER MEMBER NAME: ";
    cin.ignore();
    getline(cin, name);

    cout << "ENTER MEMBER ID: ";
    cin >> id;

    for (member &m : member_acc) {
        if (m.id == id) {
            cout << "ACCOUNT WITH THIS ID ALREADY EXISTS!!!" << endl;
            return;
        }
    }

    cout << "ENTER MEMBER PASSWORD: ";
    cin.ignore();
    getline(cin, password);

    cout << "ENTER INITIAL BALANCE: ";
    cin >> balance;

    name = toUppercase(name);

    member_acc.emplace_back(name, id, password, balance);

    cout << "MEMBER ACCOUNT CREATED SUCCESSFULLY!!!" << endl;
}
};

int main() {
    // ALL LOCAL SCOPE VARIABLES:
    int choice;
    int admin_choice;
    string name;
    int id;
    // OBJECT CREATION:
    bank b;
    // VECTOR(MEMBER) DATABASE:
    b.add_member("SHIVANGI NIGAM", 1057, "shivangi", 71240);
    b.add_member("LAKSHYA PUNDIR", 1058, "lakshya", 73450);
    b.add_member("ARYAN GUPTA", 1059, "aryan", 70620);
    b.add_member("PRANJAL KUSHWAHA", 1061, "pranjal", 72160);
    b.add_member("AANYA SINGH", 1062, "aanya", 75840);
    b.add_member("DHRUV MATHUR", 1064, "dhruv", 73920);
    b.add_member("TOYESH SRIVASTAVA", 1065, "toyesh", 76475);
    b.add_member("BHAVAY JOSHI", 1066, "bhavay", 74830);
    b.add_member("AKSHAT VERMS", 1067, "akshat", 77690);
    b.add_member("JEEVAN R", 1069, "jeevan", 72980);
    b.add_member("TEJAS GAUTAM", 1070, "tejas", 76345);
    b.add_member("TANI SINGH", 1071, "tani", 77160);
    b.add_member("RETVIJ SHRIVASTAV", 1072, "retvij", 75470);
    b.add_member("ASLESHA", 1074, "aslesha", 78210);
    b.add_member("LAKSHAY TYAGI", 1075, "lakshay", 74140);
    b.add_member("ARYAN TIWARI", 1076, "aryan", 73560);
    b.add_member("TANISHQ PAL", 1077, "tanishq", 76980);
    b.add_member("AMISHI GARG", 1078, "amishi", 71820);
    b.add_member("VAIBHAV VERMA", 1079, "vaibhav", 75230);
    b.add_member("SHAURYA RAI", 1080, "shaurya", 77110);
    b.add_member("KUMAR DAKSH", 1081, "daksh", 74480);
    b.add_member("KRISH LALWANI", 1082, "krish", 76320);
    b.add_member("TANMAY TYAGI", 1083, "tanmay", 78560);
    b.add_member("HARSHIT CHAUDHARY", 1084, "harshit", 71780);
    b.add_member("YASH SHARMA", 1085, "yash", 79640);
    b.add_member("YASH GREWAL", 1086, "yash", 75890);
    b.add_member("ITISH SINGHAL", 1088, "itish", 74420);
    b.add_member("KARTIK AGARWAL", 1089, "kartik", 78950);
    b.add_member("ATHARV GARG", 1090, "atharv", 77320);
    b.add_member("AARADHYA SRIVASTAVA", 1091, "aaradhya", 76875); 
    b.add_member("RITVIK NEEL DAS", 1093, "ritvik", 75230);
    b.add_member("ATHARAV PANDEY", 1094, "atharav", 77890);
    b.add_member("NIRBHAY KUMAR", 1095, "nirbhay", 78420);
    b.add_member("VANYA SRIVASTAVA", 1096, "vanya", 75640);
    b.add_member("ARNAV JAIN", 1097, "arnav", 79210);
    b.add_member("ARNAV SINGH CHAUHAN", 1099, "arnav", 76140);
    b.add_member("PRIYANSH MITTAL", 1100, "priyansh", 77430);
    b.add_member("ADDHYYAN GOEL", 1101, "addhyyan", 74860);
    b.add_member("ARCHIT SRIVASTAVA", 1102, "archit", 78230);
    b.add_member("AYUSH KUMAR", 1103, "ayush", 75980);
    b.add_member("DEEP CAHUDHARY", 1104, "deep", 77210);
    b.add_member("MANSHI VERMA", 1105, "manshi", 73890);
    b.add_member("GAGANDEEP SINGH", 1106, "gagandeep", 78140);
    b.add_member("YUVRAJ KATARIA", 1107, "yuvraj", 74980);
    b.add_member("KHUSHI CHAUHAN", 1108, "khushi", 77360);
    b.add_member("HARSHIT SHARMA", 1109, "harshit", 79750);
    b.add_member("ADHIRAJ MAHESHWARI", 1110, "adhiraj", 77140);
    // VECTOR(ADMIN) DATABASE
    b.add_admin("SHASHWAT BHATT", 1056);
    b.add_admin("ATHARV VERMA", 1060);
    b.add_admin("ABHINAV GARG", 1068);
    b.add_admin("VIBHOR SINGH", 1073);
    // MAIN CODE:
    // USED WHILE TRUE LOOP FOR THE CONTINUATION OF THE PROGRAM UNTIL THE USER DECIDES TO EXIT THE PORTAL
    while(true){
        // ASCII CODE INSIDE WELCOME MESSAGE
    cout << "\n\033[1;32mWELCOME TO THE BANK MANAGEMENT SYSTEM\033[0m\n" << endl;
    cout << "PLEASE SELECT YOUR DESIGNATION: " << endl;
    cout << "1. ADMIN \n2. MEMBER" << endl;
    cout << "PLEASE SELECT YOUR TYPE OF LOGIN: ";
    // CHOICE OF SELECTION FOR ADMIN OR MEMBER LOGIN
    cin >> choice;
    if (choice == 1) {
        b.admin_login();
        string menu[] = { "1. ADD MEMBER ACCOUNT", "2. DELETE MEMBER ACCOUNT", "3. DISPLAY ALL ACCOUNTS", "4. SEARCH ACCOUNT BY ID",
        "5. SEARCH ACCOUNT BY NAME", "6. UPDATE MEMBER DETAILS","7. MANAGE LOAN APPLICATION", "8. GENERATE BRANCH REPORT",
        "9. LOG OUT" };
        for (int i = 0; i < 9; i++) {
            cout << menu[i] << endl;
        }
        cout << "PLEASE SELECT THE OPERATION TO BE PERFORMED: ";
        cin >> admin_choice;
        switch(admin_choice){
            case 1:
            b.create_member_account();
            b.looping_system();
            break;
            case 2:
            b.delete_member_acc();
            b.looping_system();
            break;
            case 3:
            b.display_all_member_accounts();
            b.display_all_admin_accounts();
            b.looping_system();
            break;
            case 4:
            cout<<"PLEASE ENTER THE ID TO BE SEARCHED: ";
            cin>>id;
            b.search_account_by_id(id); 
            b.looping_system();
            break;
            case 5:
            cout<<"PLEASE ENTER THE NAME OF THE ACCOUNT TO BE SEARCHED: ";
            cin.ignore();
            getline(cin, name);
            b.search_account_by_name(name);
            b.looping_system(); 
            break;
            case 6:
            b.update_member_details();
            b.looping_system();
            break;
            case 7:
            b.manage_loan_application();
            b.looping_system();
            break;
            case 8:
            b.generate_report();
            b.looping_system();
            break;
            case 9:
            cout<<"THANKS FOR USING THE BANK MANAGEMENT SYSTEM!!! LOGGING OUT!!!"<<endl;
            exit(0);
            break;

        }

    } else if(choice==2){
        b.member_login();
        string menu[] = { "1. VIEW ACCOUNT DETAILS","2. APPLY FOR LOAN", "3. VIEW LOAN APPLICATION STATUS",
             "4. DEPOSIT MONEY","5. WITHDRAW MONEY","6. CHECK BALANCE","7. TRANSFER MONEY","8. VIEW TRANSACTION HISTORY","9. CHANGE PASSWORD", "10. LOG OUT" };
             for(int i=0; i<10; i++){
                cout<<menu[i]<<endl;
            }
            cout << "PLEASE SELECT THE OPERATION TO BE PERFORMED: ";
            cin>>choice;
            switch(choice){
                case 1:
                b.view_account_details();
                b.looping_system();
                break;
                case 2:
                b.apply_loan();
                b.looping_system();
                break;
                case 3:
                b.view_loan_status();
                b.looping_system();
                break;
                case 4:
                b.deposit_money();
                b.looping_system();
                break;
                case 5:
                b.withdraw_money();
                b.looping_system();
                break;
                case 6:
                b.check_balance();
                b.looping_system();
                break;
                case 7:
                b.transfer_money();
                b.looping_system();
                break;
                case 8:
                b.view_transaction_history();
                b.looping_system();
                break;
                case 9:
                b.change_member_password();
                b.looping_system();
                break;
                case 10:
                cout<<"THANKS FOR USING THE BANK MANAGEMENT SYSTEM!!! LOGGING OUT!!!"<<endl;
                exit(0);
                break;
            }


    } else{
        cout<<"THE USER HAVE CHOSEN INCORRECT OPTION!! PLEASE TRY AGAIN!!"<<endl;
    }
    
}
}