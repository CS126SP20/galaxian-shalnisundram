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
   - Plan to look into testing by fixing my catch2 and CONFIG errors and also seeing if testing is necessary for the game
 
-- **5/3/2020** Inserted Title Page and User Restrictions
   - Implemented a title page that only allows the user to select a level before the game starts
   - Still need to fix testing issue and decide if testing is still necessary

-- **5/4/2020** Implemented Game Structure with Timer 
   - Included a win and lose system by implementing a timer with the help of a Timer object
   - Used game states to start and stop the game, followed by printing text to inform the user if they won or lost
   - Plan to work on the game's aesthetics and to continue trying to fix my testing issue
   
-- **5/5/2020** Made Efforts to Fix Testing Error for Possible Testing
   - Made Piazza posts and sought help from CAs, peers, and other coders to help fix catch2 and CONFIG failure
   - Realized that testing would not be essential to the code since the game output is straightforward
   - To Do: Clean/Refine code (insert constants, make more modular), continue looking into testing, improve aesthetics
   - If time: Move the enemies in a more interesting way
    