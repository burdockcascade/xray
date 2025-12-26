# XRay Engine
This project is Work-in-Progress and it needs a better name.

## Example Usage

### Example 1: Simple Hello World Application
```xml
<application>

    <!-- Window configuration -->
    <window title="Hello, World!" height="600" width="800"/>

    <!-- Scene definitions -->
    <scenes>
        <scene name="main">
            <layer id="mainLayer">
                <label id="greeting" text="Hello, World!" x="50" y="50" font-size="56" color="blue"/>
            </layer>
        </scene>
    </scenes>

</application>
```

### Example 2: Displaying a Texture
```xml
<application>

    <!-- Window configuration -->
    <window title="Hello, World!" height="600" width="800" fps="60"/>

    <!-- Asset definitions -->
    <assets>
        <texture id="exampleTexture" path="examples/sample.png" />
    </assets>

    <!-- Scene definitions -->
    <scenes>
        <scene name="main">
            <layer id="backgroundLayer">
                <sprite id="exampleSprite" x="400" y="300" texture-id="exampleTexture" />
            </layer>
        </scene>
    </scenes>

</application>
```