# 🏦 Bank Management System

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![OOP](https://img.shields.io/badge/Paradigm-OOP-orange.svg)
![Inheritance](https://img.shields.io/badge/Concept-Inheritance-purple.svg)
![STL](https://img.shields.io/badge/STL-Vectors-green.svg)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen.svg)

A full-featured, terminal-based **Bank Management System** in C++ that models real banking operations — account management, deposits, withdrawals, peer-to-peer transfers, loan applications, and transaction history — across two distinct portals: **Admin** and **Member**. Built around a proper class hierarchy using inheritance, this project goes well beyond a simple CRUD exercise into genuine financial-system logic, including balance validation, session state tracking, and audit-style reporting.

---

## 🧠 Why This Project Matters

A library or inventory system only has to track "what exists." A banking system has to track **what exists, who owns it, how much of it there is, and who's allowed to move it** — and it has to get the arithmetic right every single time. This project tackles that head-on: every money-moving operation (deposit, withdrawal, transfer, loan approval) is validated against real constraints — insufficient funds, self-transfers, duplicate IDs — and logged into a transaction ledger. It's a compact but faithful simulation of the kind of state management real banking software has to get right.

---

## ✨ Core Features

### 🔐 Dual Authentication System
- **Admin login** — 4-digit access-code verification against the registered admin database, with a 3-attempt lockout.
- **Member login** — ID + password verification (passwords accepted via `getline` so they can include spaces), also with a 3-attempt lockout.
- A `loggedInMember` pointer tracks the active session so every subsequent member operation (deposit, transfer, loan, etc.) automatically applies to the correct account — no need to re-enter an ID for every action.

### 🧑‍💼 Admin Portal
| Capability | Description |
|---|---|
| Add Member Account | Registers a new member with name, ID, password, and opening balance |
| Delete Member Account | Removes a member account by ID, with confirmation display |
| Display All Accounts | Lists every member and admin account in the system |
| Search by ID | Instant lookup of a specific member account |
| Search by Name | Case-insensitive name search (custom uppercase normalizer) |
| Update Member Details | Edit a member's name or password, with Y/N confirmation before committing |
| Manage Loan Applications | View, approve, or reject pending loan requests |
| Generate Branch Report | Prints a full audit view: all members, all admins, all loans, all transactions |

### 🙋 Member Portal
| Capability | Description |
|---|---|
| View Account Details | Displays the logged-in member's profile |
| Apply for Loan | Submits a loan request tied to the authenticated session |
| View Loan Status | Checks whether a loan application is still pending |
| Deposit Money | Adds funds to the account, validated against non-positive input |
| Withdraw Money | Removes funds, blocked if the amount exceeds the current balance |
| Check Balance | Instantly displays current account balance |
| Transfer Money | Peer-to-peer transfer to another member by ID, with self-transfer and insufficient-balance protection |
| View Transaction History | Shows every deposit, withdrawal, and transfer involving the account |
| Change Password | Requires current password verification, blocks reusing the old password, and requires new-password confirmation |

---

## 🏗️ Architecture & Class Design

The system is built on a proper **inheritance hierarchy** rather than flat, duplicated classes:

```
                 ┌───────────────┐
                 │    account     │   (base class)
                 ├───────────────┤
                 │ name           │
                 │ id             │
                 │ display()      │
                 └───────────────┘
                    ▲          ▲
       ┌────────────┘          └────────────┐
┌───────────────┐                    ┌───────────────┐
│    member      │                    │     admin     │
├───────────────┤                    ├───────────────┤
│ -password      │ (encapsulated)     │ (inherits      │
│ +balance        │                    │  name & id)    │
│ get_password()  │                    │ display()      │
│ set_password()  │                    │ (overridden)   │
│ display()       │ (overridden)       └───────────────┘
└───────────────┘

        ┌──────────────┐         ┌──────────────┐
        │     Loan      │         │ transaction   │
        ├──────────────┤         ├──────────────┤
        │ name, id      │         │ sender/receiver│
        │ amount         │         │ id & name      │
        │ display()      │         │ amount          │
        └──────────────┘         └──────────────┘
                  ▲                       ▲
                  └───────────┬───────────┘
                              │
                      ┌──────────────┐
                      │     bank      │   (orchestrator)
                      ├──────────────┤
                      │ vector<member> │
                      │ vector<admin>  │
                      │ vector<Loan>   │
                      │ vector<transaction>│
                      │ member* loggedInMember │
                      ├──────────────┤
                      │ all business logic: │
                      │ login, transact,    │
                      │ loans, reports       │
                      └──────────────┘
```

- **`account`** — The shared base class holding `name` and `id`, demonstrating **hierarchical inheritance** as the common ancestor of both user types.
- **`member`** — Inherits from `account` and adds a **private, encapsulated** `password` field (accessible only through `get_password()` / `set_password()`) plus a live `balance`. Overrides `display()` to mask the password and show balance instead — a direct demonstration of **polymorphism**.
- **`admin`** — Also inherits from `account`, with its own overridden `display()`, proving the same base class can support two genuinely different roles.
- **`Loan`** — An independent record type representing a pending or processed loan request.
- **`transaction`** — An immutable ledger entry capturing sender, receiver, and amount for every money movement.
- **`bank`** — The aggregator class. Owns four vectors (members, admins, loans, transactions) and a raw pointer (`loggedInMember`) that represents session state, exposing all banking logic as clean member functions so `main()` stays focused purely on menu navigation.

---

## ⚙️ Technical Highlights

- **Inheritance** — Both `member` and `admin` derive from a shared `account` base, avoiding duplicated `name`/`id` logic.
- **Encapsulation** — The `password` field in `member` is `private`, only reachable through controlled getter/setter methods — a real demonstration of data hiding, not just convention.
- **Polymorphism via Method Overriding** — `member::display()` and `admin::display()` each override the base behavior to show role-appropriate information.
- **Session State via Pointers** — `member* loggedInMember` tracks the authenticated user across the entire member session, so functions like `deposit_money()` or `transfer_money()` never need an ID passed in — they act directly on the pointed-to object.
- **Real Financial Guardrails** — Every money-moving function checks for invalid (≤0) amounts, insufficient balance before withdrawals/transfers, and blocks transferring to one's own account.
- **Transaction Ledger** — Every deposit, withdrawal, and transfer pushes a `transaction` record, and `view_transaction_history()` filters the ledger to show only entries involving the logged-in member.
- **Loan Lifecycle Management** — A loan moves from `apply_loan()` (member-side) → `manage_loan_application()` (admin-side, approve/reject) → balance update or removal from the queue, modeling a believable approval workflow.
- **Defensive Input Handling** — Repeated use of `cin.ignore()` before `getline()` calls correctly clears the input buffer, preventing the classic C++ beginner bug where leftover newlines corrupt the next string read.
- **Pre-Seeded Realistic Dataset** — Launches with 45 member accounts and 4 admin accounts pre-loaded, so the system is immediately demoable.

---

## 💻 Sample Interaction

```
WELCOME TO THE BANK MANAGEMENT SYSTEM

PLEASE SELECT YOUR DESIGNATION:
1. ADMIN
2. MEMBER
PLEASE SELECT YOUR TYPE OF LOGIN: 2

PLEASE ENTER YOUR ACCOUNT ID: 1057
PLEASE ENTER YOUR PASSWORD: shivangi
LOGIN SUCCESSFUL!!!

WELCOME SHIVANGI NIGAM

1. VIEW ACCOUNT DETAILS
2. APPLY FOR LOAN
3. VIEW LOAN APPLICATION STATUS
4. DEPOSIT MONEY
5. WITHDRAW MONEY
6. CHECK BALANCE
7. TRANSFER MONEY
8. VIEW TRANSACTION HISTORY
9. CHANGE PASSWORD
10. LOG OUT
PLEASE SELECT THE OPERATION TO BE PERFORMED: 7
ENTER RECEIVER ACCOUNT ID: 1058
ENTER AMOUNT TO TRANSFER: 5000
AMOUNT TRANSFERRED SUCCESSFULLY!!!
YOUR UPDATED BALANCE: 66240
```

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler supporting C++11 or later (e.g., `g++`)

### Compile & Run
```bash
g++ bank_management_system.cpp -o bank
./bank
```
> 💡 Sample login — Member ID `1057`, password `shivangi`. Sample Admin access code: `1060`.

---

## 🔭 Future Enhancements

This was built as a deep dive into inheritance, encapsulation, and stateful session logic. The natural next steps toward a production-grade version:
- **Real password hashing** — passwords are currently stored and compared as plaintext strings (only masked on display); a production system would hash them (e.g., with bcrypt) rather than store raw text.
- **Separate admin credentials** — admin login currently authenticates against ID alone; adding a dedicated admin password field would close an obvious gap.
- **Persistent storage** — save all four ledgers (members, admins, loans, transactions) to disk or a database so data survives restarts.
- **Interest & loan terms** — extend the `Loan` class with interest rate, tenure, and repayment scheduling instead of a single lump-sum approval.
- **Exception handling** — guard numeric inputs against non-numeric entry to prevent undefined input-stream behavior.
- **Multi-currency / decimal support** — balances currently use integer types, which wouldn't support paise/cents in a real deployment.

---

## 👤 Author

**Atharv Verma**
B.Tech, Computer Science and Engineering — SRM Institute of Science and Technology
📧 verma.atharv@gmail.com

---

*Part of a series of OOP-driven systems projects exploring how inheritance, encapsulation, and pointer-based state management combine to model real-world transactional software.*
