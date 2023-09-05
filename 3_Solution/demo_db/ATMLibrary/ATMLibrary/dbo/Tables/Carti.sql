CREATE TABLE [dbo].[Carti]
(
	[Id] INT NOT NULL PRIMARY KEY, 
    [Titlu] NCHAR(40) NOT NULL, 
    [Autor] NCHAR(40) NULL, 
    [An_publicare] NCHAR(20) NULL
)
