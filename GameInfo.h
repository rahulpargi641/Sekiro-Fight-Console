#pragma once

#include <iostream>


class GameInfo
{
public:
    const std::string Player1 =

        R"("Sekrio : A Shinobi serving the Divine Heir, Kuro
 Info:
1. Weapons - Wields Katana named Kusabimaru given by Kuro and the small sword Sabimaru.
2. Stats- 
    A. Vitality - Average - 200                               
    B. Attack1- Floating passage - Unleash Attack using Kusabimaru in a flowing, dance like form, overwhelming enemies in a favor of graceful aggression.                                        
                                   Inflicts High Damage = 30.
    C. Attack2 - Piercing Sabimaru - The blue rust poison on Sabimaru's blade eats its way into enemies and Poison them. Enemy's vitality will degenerate for a time.
                                   Vitality Degeneration rate =  3/sec, Duration = 15s, Damage = 3.
3. Heal - Healing Gourd - A gourd filled with Vitality restoring medicine, Restores the Vitality.
                          Total = 5, Vitality Gain = 100
4. Cosumable Items - 3
    A. Ungo's Sugar - Candy made in Senpou Temple, imbued with Ungo's blessing. Reduces damage to one's Vitality for a time.
                      Duration - 30 seconds. Incoming Damage will be Half.
5. Ability - Ceremonial Tanto - Dagger with a stark white blade. Converts Vitality into Spirit Emblems. Perform a ritual and receive spirit emblems for the exchange of own's 
             50% of the vitality.
             Spirit Emblems are needed to draw Mortal Blade, Mortal blade consumes spirit emblems.
             Mortal Blade - Crimson blade allows one to defeat even infested beings. Deals Critical Damage.
             Mortal Blade Damage - 500% More than base damage.
                                           
 )";

    const std::string Player2 =

        R"("Genichiro : A Samurai, current leader of Ashina clan and pupil of the mysterious Lady Tomoe, the okami worrior the of Fountainhead Palace.
Info:
1. Weapons - Weilds Katana and a Bow.
2. Stats-
   A. Vitality - High - 300
   B. Attack1 - Ashina Cross - A secret technique of Ashina style, devoted to the mastery of a swift kill. Draws a cruciform cut in the blink of 
                               an eye. Inflicts very high damage. = 50
      Attack2 - Divine Arrow Storm - A long distant attack allows genichiro to recover vitality while attacking. 
                               Damage = 30. Vitality Regeneration Rate = 1/sec. Duration = 15s
3. Heal - Pellet - Medicinal Pellets that slowly restore Vitality, A secret treatment passed down for generations in the land of Ashina.
                   Total = 3, Vitality Regeneration Rate  = 3/seconds, Duration  = 15s.
4. Consumable Items - 3
   A. Mist orb - When orb bursts, the mist it leaves behind, Enemies will be unable to use items like the Healing Gourd and sugar candies for a time.
                 Duration  = 30 seconds
5. Ability - Resurrection, Way of Tomoe, When genichiro dies, due to effects of rejuvenating waters of Fountainhead Palace, will come back to life, and channels the power of lightning on his blade 
             and arrows through the Way of Tomoe, a technique he acquired from Lady Tomoe. 
             Lighting stunts the enemy for 10 seconds, Enemy will not be able to move, this attack allows genichiro to keep attacking for the next 10 seconds. Damage Done = 20;   
 )";

    const std::string Player3 =
        R"(Senpou Priest : 
Info: One of the monks who have been corrupted by their obsession with the undying. 
1. Weapons - None
2. Stats- 
   A. Vitality - High - 300
   B. Attack1 - Praying strikes - Using successive elbow and arm strikes, unleash a flurry of quick attack. The strikes are both martial art and form of prayer. 
	            "Without strength one cannot defeat the enemies of Buddha". 
                Inflicts average Damage  = 20
      Attack2 - None.
3. Heal - Divine Grass - One small part of Ashina is exceedingly old. The ancient soil, rocks, and water that pervaded the land are said to 
                have attracted the attention of the gods. The doctor Dogen studied the plants in this ancient place, resulting in the recipe for 
                this special medicine.
                Fully restores vitality. Total = 3.
4. Consumable Items - 6 
   A. Ako's Sugar - Sugar candy made in Senpou Temple, sustaining Ako's blessing. Boosts Attack Power for a time.
                    Duration = 30s seconds, Attack Power Boost = 150%.
   B. Ungo's Sugar - Sustaining Ungo's blessing. Temporarily reduces Vitality damage.
                     Duration = 30s seconds, Incoming Damage will be Half.
   C. Yashariku's Sugar - Sustaining Yashariku's blessing. Halves max Vitality, while granting a large Attack Power Boost. 
                          Duration = 30s seconds, Attack Power Boost = 100% , Vitality gain = 50% of base vitality
5. Ability - None

)";
    const std::string Player4; // Player4 - Red knight Guard, yet to Implement, not needed as per the assignment
    const std::string Player5; // Player5 - Okami Worrior, yet to Implement, not needed as per the assignment 

    void DisplayInfo();
    void ShowPlayerInfo(int PlayeNo) const;
   
};
