# 📂 MiniGit

A Git-inspired Version Control System developed using **C++** for backend logic and **Python Streamlit** for the graphical user interface.

---

## 📌 Project Overview

MiniGit is a lightweight version control system that implements the basic functionalities of Git. It allows users to initialize repositories, stage files, create commits, check repository status, view commit history, and checkout previous commits through an interactive Streamlit interface.

This project was developed as an educational implementation to understand how version control systems work internally.

---

## ✨ Features

- 🚀 Initialize Repository
- 📄 Check Repository Status
- ➕ Add Files to Staging Area
- 💾 Commit Changes
- 📜 View Commit History
- 🔄 Checkout Previous Commits
- 📊 Dashboard with Repository Statistics
- 💻 Interactive Streamlit User Interface

---

## 🛠 Tech Stack

### Backend

- C++
- Object-Oriented Programming
- File Handling
- STL

### Frontend

- Python
- Streamlit

---

## 📁 Project Structure

```
MiniGit/
│
├── frontend/
│   └── app.py
│
├── src/
│   ├── main.cpp
│   ├── Repository.cpp
│   ├── Repository.h
│   ├── Commit.cpp
│   ├── Commit.h
│   ├── FileManager.cpp
│   ├── FileManager.h
│   ├── Hash.cpp
│   ├── Hash.h
│   ├── Utils.cpp
│   └── Utils.h
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

---

## ⚙️ Installation

### Clone the repository

```bash
git clone https://github.com/Shubhangi-bee/MiniGit.git
```

### Navigate into the project

```bash
cd MiniGit
```

### Build the project

```bash
mkdir build
cd build
cmake ..
make
```

---

## ▶️ Run Backend

```bash
./minigit
```

---

## ▶️ Run Frontend

```bash
cd frontend
streamlit run app.py
```

---

## 📷 Screenshots

### Dashboard

(Add dashboard screenshot here)

### Add File

(Add add file screenshot here)

### Commit History

(Add commit history screenshot here)

---

## 🚀 Future Enhancements

- Branch Support
- Merge Functionality
- File Difference Viewer
- Repository Tree Viewer
- Search Commit History

---

## 👩‍💻 Developed By

**Shubhangi**

---

## 📜 License

This project is developed for educational purposes.