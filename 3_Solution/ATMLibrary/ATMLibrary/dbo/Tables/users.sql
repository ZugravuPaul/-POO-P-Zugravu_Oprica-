CREATE TABLE [dbo].[users] (
    [id]       INT            IDENTITY (1, 1) NOT NULL,
    [nume] NCHAR(10) NULL, 
    [prenume] NCHAR(10) NULL, 
    [username] NVARCHAR (255) NOT NULL,
    [password] NVARCHAR (255) NOT NULL,
    [email]    NVARCHAR (255) NOT NULL,
    PRIMARY KEY CLUSTERED ([id] ASC),
    UNIQUE NONCLUSTERED ([email] ASC)
);

