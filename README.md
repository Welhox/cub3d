CUB3D, a raycasting project.

In this project, I and tcambel22 made a Wolfenstein 3D style raycaster.
It uses DDA algorith to calculate the length of the rays to walls (or other objects), and uses this information to generate
a world, one pixel row at a time. If you do "make base", then it makes a base program, which takes a base .cub file from the maps
folder as argument. This game only renders walls, and sky / floor as a single colour from the file.
In order to make the acctual game just run "make". This will make a cub3D executable which takes a .cub file from the maps folder,
ie lvl1.cub.
This version renders the same as the base model, but also renders textures for floor, ceiling, doors and sprites. In order to speed
up processing, we decided to thread the floor, ceiling and sprite calculations to their respective threads. This gave us
a clear improvement in performance. The game also includes wall collision, catchable ducks, minimap and catchable ducks.

To play the game launch the executable with a map as argument.

W/S & arrow up/down moves the player forward and back.
A/D strafes left & right.
Left/right arrows or moving mouse turns the player around.
Doors can be opened/closed with E or left mouse button.
Ducks can be caught/released wit hE or left mouse button.

CATCH ALL THE DUCKS TO WIN!

The levels are the same, except for different textures used.
lvl1.cub
![Screenshot from 2024-09-17 11-22-27](https://github.com/user-attachments/assets/20db01ef-53dc-46bc-84a5-9f5453018080)
![Screenshot from 2024-09-17 11-23-03](https://github.com/user-attachments/assets/275fc002-77ea-45b3-a1c7-f1b4ef856118)

lvl2.cub
![Screenshot from 2024-09-17 11-23-16](https://github.com/user-attachments/assets/bc96a387-bfd7-4c94-866f-4c277f3fe88f)
![Screenshot from 2024-09-17 11-23-24](https://github.com/user-attachments/assets/6369a370-480a-4c3b-8411-8cdc2f076d2a)
![Screenshot from 2024-09-17 11-24-02](https://github.com/user-attachments/assets/0f58a78f-4313-4b27-a84f-cccdb71945bc)
![Screenshot from 2024-09-17 11-24-17](https://github.com/user-attachments/assets/bf6dcab3-be83-4bf1-97d1-719d45c0d7b5)

lvl3.cub
![Screenshot from 2024-09-17 11-24-41](https://github.com/user-attachments/assets/e939044e-7efc-4501-bf92-02cddeecc4ca)
![Screenshot from 2024-09-17 11-25-02](https://github.com/user-attachments/assets/65e435c5-feab-4445-a8e9-e1c4feca22a2)

lvl4.cub
![Screenshot from 2024-09-17 11-25-26](https://github.com/user-attachments/assets/dbd2a92d-a3bc-4d8d-ac70-d70351fdaa8d)
![Screenshot from 2024-09-17 11-25-41](https://github.com/user-attachments/assets/84ef99cb-3725-4b7f-a1a6-96565764f129)
![Screenshot from 2024-09-17 11-26-06](https://github.com/user-attachments/assets/28f41d57-d14c-4bd2-8c9a-b56103c98bcf)

lvl5.cub
![Screenshot from 2024-09-17 11-26-20](https://github.com/user-attachments/assets/c7dae9ea-266f-4679-8553-15d679d8761f)
![Screenshot from 2024-09-17 11-26-47](https://github.com/user-attachments/assets/53cb655c-0540-400f-a682-d6771ca516c8)
![Screenshot from 2024-09-17 11-26-53](https://github.com/user-attachments/assets/1bd015e8-df36-4029-99ae-785e0513984c)

lvl6.cub
![Screenshot from 2024-09-17 11-27-08](https://github.com/user-attachments/assets/c0eac689-43ba-4aca-9aa9-f652eff9d01d)
![Screenshot from 2024-09-17 11-27-16](https://github.com/user-attachments/assets/fe9213bb-f1e6-4770-bb92-66ca4a6f093b)
![Screenshot from 2024-09-17 11-27-35](https://github.com/user-attachments/assets/8ff0b2c0-9ee2-4aa7-9a24-e160363b350a)

base1.cub
![Screenshot from 2024-09-17 11-28-04](https://github.com/user-attachments/assets/b0fe7997-46d3-4c3d-b114-24058b82fa74)
![Screenshot from 2024-09-17 11-28-14](https://github.com/user-attachments/assets/7e647b39-81ec-473a-a485-ddeb0207970c)

base2.cub
![Screenshot from 2024-09-17 11-28-33](https://github.com/user-attachments/assets/c90f62cc-da32-4d51-9fa5-dfc43fcbef9a)
![Screenshot from 2024-09-17 11-28-49](https://github.com/user-attachments/assets/484310ed-4cd1-4876-9fd3-38d86528f18d)
![Screenshot from 2024-09-17 11-28-58](https://github.com/user-attachments/assets/cd0160b4-5ea7-4073-9faa-7c1bf7cb52c2)



