# Development

-- **4/25/20** Finalized Addition/Removal Of .h and .cpp Files
 - Still need to put sample.cpp contents into my_app.cc
 - Still need to split sample.cpp contents into a .h and .cc file

-- **4/26/2020** Experimented with Possible Data Types of the Main Game Components
  - For instance, tinkered with the idea of how to have enemies flow across the screen 
  (i.e. should they be stored in a vector?)
  - Decided to make game levels represented by toggles, decided that the gun would simply be a rectangle
  
-- **4/27/2020** Implemented functions to move and enemy and gun across the screen
  - Implemented methods such as MoveGun(), MoveRight(), MoveLeft(), etc.
  - Still need to insert KeyEvents to change gun direction, make more than one enemy move across the screen
  
-- **4/28/2020** Refined/Cleaned Code and Implemented Methods to Move Multiple Enemies
  - Edited GetAllEnemies() method to move multiple enemies
  - Split sample.cc code into .h and .cc files
  - Still need to insert KeyEvents and shoot bullets at enemies
  
-- **5/1/2020** Create Bullets that Shoot Upward
  - Created bullet class, implemented DrawBullet() and MoveBullet()
  - Still need to erase enemies once a bullet hits them
    
-- **5/2/2020** Erased Enemies that have been hit and inserted audio 
   - Implemented CheckEnemyAlive(), KillEnemy() and bool variable for each enemy 
   - Implemented EraseHitEnemy() which uses the distance formula to determine if bullet hit enemy
   - Implemented PlayLaserAudio() and PlayEnemyPopAudio() to play audio
   - Plan to implement a game structure with a beginning and end and a different sin motion for enemies
 
