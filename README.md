#   Multiplayer_ConnectingPlayers
##  Connecting Players via local network in unreal engine 4

### Learning the basic client server model and getting multiple instances connected through a collaborative puzzle game.


* Client and Server aproach and why It is better than peer-to-peer 
  creating mini-network using Local IP Address through CMD "(ue4 path)" "(Game path)" -server -log
  "(ue4 path)" "(Game path)" LOCAL_IP:LISTENING_PORT -game -log

* The replication and authority -> the server is always right and Has the authority to replicate other actors , the server has the upper hand 
  upon the client, we used SetReplicates(true) and SetReplicateMovement(true) to enable it.

* how NATs "Network Address Translation" work and the differences between local and global network. Connecting to two players using Hamachi by creating a new network then launch server on the this current network and launch the 
  client on the other pcs "(ue4 path)" "(Game path)" -server -log
  "(ue4 path)" "(Game path)" LOCAL_IP:LISTENING_PORT -game -log

* Handling overllaping events in C++ , Using OnComponentBeginOverlap and OnComponentEndOverlap along with the two void functions OnOverlapBegin and OnOverlapEnd.

* GameInstance exists in whenever I run the game, we are trying to connect using game instance and command line, difference between constructor and Init() that init fires only when the game starts and it fires
  at every running instance of the game. We created a custome gameinstance based on the gameinstance class and overrided in the project settings by searching for GameInstance in the search bar.

* Using UEngine* Engine = GetEngine(); to add on screen debug message , we also used "Exec" in the UFUNCTION  and this allows us to use the game CMD when " ~ " pressed , The Exec is compatible in
  (PlayerControllers, Possessed Pawns, HUDs, Cheat Managers, Game Modes, Game Instances)

* Hosting the server with the server travel in the GetWorld member, the playercontroller connects to a map(lobby) then when the command Host is fired, it fires ServerTravel and takes the player from first map to the 2nd one and Host  a server so that clients can start connecting to this server.
