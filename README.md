# ☕ Café Digital System (CDS) – OOP Edition
  
This project digitally simulates a university café system using modern programming paradigms — including class design, inheritance, polymorphism, file handling, and dynamic memory.

---

## 🎯 Objectives

- Apply core **OOP concepts**: Encapsulation, Inheritance, Polymorphism
- Implement a **menu-driven** user interface with real-world role simulation
- Use **file handling** to maintain persistent data for stock and credentials
- Structure the project into **classes and modules** for maintainability

---

## 👨‍💼 Roles and Features

### 🛠️ Admin Panel
- Full access to café inventory
- Add, remove, update, and search stock items
- View notifications for low stock (🔴) or empty items (🟡)
- Handle employee and user credentials
- Respond to student/staff complaints
- Monitor bestseller employees and sales stats

### 👩‍🍳 Employee Panel
- Secure login (min. 5 users)
- Take and record orders
- Generate digital transactions
- View and respond to scheduled orders
- Search available items

### 🎓 Student/Staff Access
- Place/schedule orders
- Search menu items
- Submit complaints
- View café announcements and promotions

---

## 🧱 System Components (OOP)

### ✅ Classes (suggested structure):
- `User` (Base class)
  - `Admin` (inherits User)
  - `Employee` (inherits User)
- `StockItem`
- `Order`
- `Complaint`
- `Transaction`
- `CDSSystem` (Manager/controller class)

Each class handles its own data and operations using encapsulation and abstraction.

---

## 💾 File Handling

Persistent storage is done via text files:
- `users.txt` – Employee/admin credentials
- `stocks.txt` – Item details (Name, Qty, Price, Total Price)
- `orders.txt` – Scheduled/online orders
- `complaints.txt` – Customer feedback

---

## 📈 Sales and Analytics

- Track sales by comparing item quantity before and after each day
- Show most and least sold items
- Highlight best-performing employees
- Calculate average and total stock value

---



