# CLASS DESCRIPTIONS
This description guide will skip - __getters__ & __setters__ & __constructors__ - and focus on less known functions and describing what all attributes do. There will be special cases where there will be a constructor or a setter in a table

**ONLY PUBLIC METHODS ARE SHOWN**, considering that private and protected methods are not meant to be used


- [GameObject](#gameobject)
- [Collider](#collider)


## GameObject
### Attributes  
| Accessabilty | Type                   | Name       | Description                                                  |
| ------------ | ---------------------- | ---------- | ------------------------------------------------------------ |
| Private      | float                  | x          | Used in components for position                              |
| Private      | float                  | y          | Used in components for position                              |
| Private      | float                  | mirrorX    | Used to calculate offset coordinates from parent             |
| Private      | float                  | mirrorY    | Used to calculate offset coordinates from parent             |
| Private      | float                  | z          | Used to determine which gameobject to draw first             |
| Private      | string                 | objectName | Can be used for debugging or finding gameobjects             |
| Private      | string                 | tag        | Used in gameobject finding and in Collider helpers           |
| Private      | [Collider*](#collider) | collider   | Can be used in collision detection                           |
| Private      | bool                   | isChild    | Is a flag that stores info if gameobject is a child          |
| Private      | GameObject*            | parent     | Used to update gameobject children                           |
| Private      | vector<GameObject*>    | children   | Every frame these gameobjects get updated as children        |
| Private      | vector<Drawable*>      | drawables  | Every frame this vector gets re-read from main loop and stores drawable components |
| _static_ | int | objectCount | Used in default gameobject creation for objectnames |
| _static_ | vector<GameObject*> | objects | Used in engine main-loop. Stores all created gameobjects |

### Methods
| Return type | Name | Description |
| ----------- | ---- | ----------- |
| vector<GameObject*> | getAllObjects() | **STATIC** Returns all created gameobjects until calling this method |
| vector<GameObject*> | getParentObjects() | **STATIC** Returns all gameobjects that are **NOT** flagged as child |
| vector<GameObject*> | getChildObjects() | **STATIC** Returns all gameobjects that are flagged as child |

## Collider
