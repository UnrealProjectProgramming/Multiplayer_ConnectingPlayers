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

# How to connect: 1- Each player must have a copy the final built game
				   2- both players must connect via Hamachi 
				   3- after that the players open the game and press "`" and connect to the Local Host IP
__________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

## Starting to create an advanced user interface MainMenu to make it easier for players to connect without the need of using in game command line.  

* Getting a reference to a BP Class using FClassFinder and including "UMG" in the Build.CS script to use U.I Functionality.

* creating a LoadMenu function in C++ which is BlueprintCallable , in this function we used CreateWidget (instance, UCLass)  and added the created widget to viewpot, then Used the LoadMenu Func to call it from level blueprint in BeginPlay. 

* we changed the UI input mode using APlayerController Function with the name SetInputMode, SetInputMode takes FInputMode as an Arguement m and we constructed FInputModeUIOnly SetWidgetToFocus and SetLockMouseToViewPortBehaviour and then we passed it to SetInputMode and made the cursor visiable.

* Making Advanced UI layoyt by using vertical and horizontal boxes as well as Size boxes and learning about Overlaying.

* connecting UMG with C++ "Binding" http://benhumphreys.co.uk/unreal/ui-bindwidget/    https://docs.unrealengine.com/latest/INT/API/Runtime/UMG/Components/UButton/

* using UButton callback (OnClick) to AddDynamic event so we can be able to connect with Host function in the PuzzlePlatformGameInstance.

* implementing Unreal interface and making sure not to cause the Diamond inheritance problem https://medium.freecodecamp.org/multiple-inheritance-in-c-and-the-diamond-problem-7c12a9ddbbec  , so that we make the MenuSystem independant as it will call the interface and the GameInstance will call the interface as well , so the Host func can be called from the MainMenu class to the interface then to its way to the GameInstance Class.

* Creating Sub Menu for join a server and styling it , and adding a switcher to switch between menu systems.

* Navigating Menus in C++ by creating a menu switcher in the UI then bind it to the c++ by using Meta = BindWidget in UPROPERTY after that we Bind the action by creating a function then AddDynamic in the UMainMenu::Initialize. and the the created function we use WidgetSwitcher->SetActiveWidget and pass to it the Widget that we want to navigate to whether the MainMenu or the joinMenu  https://docs.unrealengine.com/latest/INT/API/Runtime/UMG/Components/UWidgetSwitcher/index.html

## Finishing Section two and full creating the MainMenu and ready to advance and add more on it.

* Game tested and everything working fine.

________________________________________________________________________________________________________________________

# Multiplayer_Steam
## Using Steam SDK and UnrealEngine 4 online Sub-System to make a multiplayer functionality ##

* Getting steam SDK

* Fixing Direct3D common error " S1023 " and updating & connecting the SteamworksExample.sln to D3dx to run steam game example " space war " and have access to use steam features such as seeing friends ,  voice chat , server and lobby and even making steam achievments.

* Connecting to friends over steam Spacewar , Online and localy.

* IOnlineSubsystem  https://docs.unrealengine.com/latest/INT/Programming/Online/

* Memory management in C++ Ue4 ( Reference counting and garabage collecting) https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/SmartPointerLibrary/  https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Objects/Optimizations/

* creating session and using OnCreateSessionCompletedDelegate https://docs.unrealengine.com/latest/INT/Programming/Online/Interfaces/Session/index.html#matchmaking-findingsessions
 https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Delegates/Multicast/
 https://docs.unrealengine.com/latest/INT/API/Plugins/OnlineSubsystem/Interfaces/IOnlineSession/index.html


* Joining A Session , using SessionInterface->JoinSession to join a session passing to it player index and session name and the searchresults at a current Index, after that we call OnJoinSessionCompleteDelegate and pass to it the function that it wants which is OnJoinSessionComplete whichs takes two params , the Servername and EOnJoinSessionCompleteResult::Type after that we go to the the OnSessionComplete and we implement it , we first  pass an out FString Address to SessionInterface->GetResolvedConnectString and we check if it fails we return otherwise , we find the world and the player controller and make a client travel using the Out Address that we recived from GerResolved ConnectString. 
Check These Links if needed.
https://docs.unrealengine.com/latest/INT/Programming/Online/Interfaces/Session/index.html
https://docs.unrealengine.com/latest/INT/API/Plugins/OnlineSubsystem/Interfaces/IOnlineSession/JoinSession/1/index.html
https://docs.unrealengine.com/latest//INT/API/Plugins/OnlineSubsystem/Interfaces/IOnlineSession/GetResolvedConnectString/1/index.html
https://docs.unrealengine.com/latest/INT/API/Plugins/OnlineSubsystem/Interfaces/FOnJoinSessionComplete/index.html

* Enabling Steam Online Subsystem , we first need to go and include it in the Build.cs OnlineSubsystemSteam" then we  change the Engine.ini using what is in this documentation.
	https://docs.unrealengine.com/latest/INT/Programming/Online/Steam/    check out at the end of the page ( the End Results ).