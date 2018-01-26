# Multiplayer_ConnectingPlayers
Connecting Players via local network in unreal engine 4

Learning the basic client server model and getting multiple instances connected through a collaborative puzzle game.


* Client and Server aproach and why It is better than peer-to-peer 
  creating mini-network using Local IP Address through CMD "(ue4 path)" "(Game path)" -server -log
  "(ue4 path)" "(Game path)" LOCAL_IP:LISTENING_PORT -game -log

* The replication and authority -> the server is always right and Has the authority to replicate other actors , the server has the upper hand 
  upon the client, we used SetReplicates(true) and SetReplicateMovement(true) to enable it.
