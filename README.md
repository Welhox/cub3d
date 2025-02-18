# CUBE3D  

A **2.5D raycaster** created in C using low-level graphics, inspired by **Wolfenstein 3D**.  

![Gameplay GIF](https://github.com/Welhox/cub3d/blob/main/assets/CUB3D-GIF.gif)  

## 📌 Table of Contents  

- [About the Project](#about-the-project)  
- [Features](#features)  
- [Installation & Compilation](#installation--compilation)  
- [Usage](#usage)  
- [Controls](#controls)  
- [Levels & Screenshots](#levels--screenshots)  
- [Base Mode](#base-mode)  
- [Contributors](#contributors)  

---

## 🕹️ About the Project  

In this project, **[@Welhox](https://github.com/Welhox(me) and [@tcampbel22](https://github.com/tcampbel22)** developed a **Wolfenstein 3D-style** raycaster using the **DDA (Digital Differential Analyzer) algorithm**. The game constructs the 3D world one **pixel row at a time** by computing ray distances to walls and objects.  

To optimize performance, we implemented **multithreading** for rendering the **floor, ceiling, and sprites**, leading to a **noticeable performance boost**.  

---

## ✨ Features  

✔️ **Raycasting Engine** – Based on the **DDA algorithm**  
✔️ **Multithreaded Rendering** – Faster processing for **floor, ceiling, and sprites**  
✔️ **Textured Walls & Objects** – Supports **custom textures**  
✔️ **Interactive Elements** – **Doors** can be opened/closed  
✔️ **Collectibles** – Catch **ducks** to win the game!  
✔️ **Minimap** – Navigate the world more easily  

---

## ⚙️ Installation & Compilation  

To build the project, use the provided `Makefile`:  

### 🔹 Full Game (Textured Mode)
```bash
make
```
This compiles the **full version**, which supports **textured** floors, ceilings, doors, and sprites.  

### 🔹 Base Mode (Minimal Rendering)
```bash
make base
```
This compiles a basic version that only renders **walls**, and a **solid-colored floor and sky** (as defined in the `.cub` map file).  

---

## 🎮 Usage  

Launch the game with a `.cub` file from the `maps/` folder:  

```bash
./cub3D maps/lvl1.cub
```

---

## 🕹️ Controls  

| Action            | Key / Input |
|------------------|------------|
| Move Forward / Backward | `W` / `S` (or `↑` / `↓`) |
| Strafe Left / Right | `A` / `D` |
| Turn Left / Right | `←` / `→` (or mouse movement) |
| Open/Close Doors | `E` or **Left Mouse Button** |
| Catch / Release Ducks | `E` or **Left Mouse Button** |

🏆 **Goal:** **Catch all the ducks to win!**  

---

## 🗺️ Levels & Screenshots  

Each level uses different textures, adding variety to the gameplay.  

### **🔹 Level 1 – `lvl1.cub`**  
![lvl1 Screenshot](https://github.com/user-attachments/assets/20db01ef-53dc-46bc-84a5-9f5453018080)  
![lvl1 Screenshot](https://github.com/user-attachments/assets/275fc002-77ea-45b3-a1c7-f1b4ef856118)  

### **🔹 Level 2 – `lvl2.cub`**  
![lvl2 Screenshot](https://github.com/user-attachments/assets/bc96a387-bfd7-4c94-866f-4c277f3fe88f)  
![lvl2 Screenshot](https://github.com/user-attachments/assets/6369a370-480a-4c3b-8411-8cdc2f076d2a)  

### **🔹 Level 3 – `lvl3.cub`**  
![lvl3 Screenshot](https://github.com/user-attachments/assets/e939044e-7efc-4501-bf92-02cddeecc4ca)  
![lvl3 Screenshot](https://github.com/user-attachments/assets/65e435c5-feab-4445-a8e9-e1c4feca22a2)  

### **🔹 Level 4 – `lvl4.cub`**  
![lvl4 Screenshot](https://github.com/user-attachments/assets/dbd2a92d-a3bc-4d8d-ac70-d70351fdaa8d)  
![lvl4 Screenshot](https://github.com/user-attachments/assets/84ef99cb-3725-4b7f-a1a6-96565764f129)  

### **🔹 Level 5 – `lvl5.cub`**  
![lvl5 Screenshot](https://github.com/user-attachments/assets/c7dae9ea-266f-4679-8553-15d679d8761f)  
![lvl5 Screenshot](https://github.com/user-attachments/assets/53cb655c-0540-400f-a682-d6771ca516c8)  

### **🔹 Level 6 – `lvl6.cub`**  
![lvl6 Screenshot](https://github.com/user-attachments/assets/c0eac689-43ba-4aca-9aa9-f652eff9d01d)  
![lvl6 Screenshot](https://github.com/user-attachments/assets/fe9213bb-f1e6-4770-bb92-66ca4a6f093b)  

---

## 🏗️ Base Mode  

The **base version** of the game features only walls and a single-color floor/sky. Distance shading is also absent.  

### **🔹 Base Map 1 – `base1.cub`**  
![base1 Screenshot](https://github.com/user-attachments/assets/b0fe7997-46d3-4c3d-b114-24058b82fa74)  
![base1 Screenshot](https://github.com/user-attachments/assets/7e647b39-81ec-473a-a485-ddeb0207970c)  

### **🔹 Base Map 2 – `base2.cub`**  
![base2 Screenshot](https://github.com/user-attachments/assets/c90f62cc-da32-4d51-9fa5-dfc43fcbef9a)  
![base2 Screenshot](https://github.com/user-attachments/assets/484310ed-4cd1-4876-9fd3-38d86528f18d)  

---

## 👥 Contributors  

- **[@Welhox](https://github.com/Welhox)**  
- **[@tcampbel22](https://github.com/tcampbel22)**  
