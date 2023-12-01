# Code Samples

This repository is a collection of code samples using the unreal engine. You can Use, Change or Redistribute the source code as you like.

## Where to start?

The main feature in this sample is the QuestGenerator.
The implementation is from the Game Bootyisland, a combination of City-builder and Action RPG, which I’m currently developing (further information and a playable preview can be found [here](https://bootyisland.itch.io/bootyisland)). 
The concept behind the QuestGenerator is that it generates random quests based on templates that can be designed at editor time. The clue: The generated quests will be embedded into the world the player has built during runtime. For example enemies that have to be defeated can be spawned at buildings of a specific type. Also, templates can be unlocked at runtime based on events that can be selected in editor time.
A good place to start is the [QuestGenerator.h](./Source/CodeSamples/Public/Components/QuestGenerator.h) file.

Additionally I added the GenericWidgets plugin, which contains code for some widgets I created. There is not a lot of code behind them, so they should be a lot easier to understand.

## Additional hints

I did not want to release the complete source code of my game and I had to find a scope for this sample. So, I thought the best way to compile a code sample that builds successfully, I decided to comment out some code that is in the original files, but would result in missing references to files I did not add.