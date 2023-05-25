CREATE TABLE [dbo].[DetinatoriCarti]
(
	[Id] INT            IDENTITY (1, 1) NOT NULL, 
    [IdUser] INT NOT NULL FOREIGN KEY references users(Id), 
    [IdCarte] INT NOT NULL FOREIGN KEY references Carti(Id)

)
