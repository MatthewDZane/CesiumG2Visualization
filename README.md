<a name="readme-top"></a>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/MatthewDZane/CesiumNetBoxVisualization">
    <img src="images/CesiumExample.png" alt="CesiumExample" width="80" height="80">
  </a>

  <h3 align="center">Cesium G2 Visualization</h3>

  <p align="center">
    A Cesium Earth based NetBox visualization!
    <br />
    <a href="https://github.com/MatthewDZane/CesiumNetBoxVisualization"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/MatthewDZane/CesiumNetBoxVisualization">View Demo</a>
    ·
    <a href="https://github.com/MatthewDZane/CesiumNetBoxVisualization">Report Bug</a>
    ·
    <a href="https://github.com/MatthewDZane/CesiumNetBoxVisualization">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)

This project is an Unreal Engine 5 Plugin that utilizes [Cesium for Unreal](https://cesium.com/platform/cesium-for-unreal/) to generate and display a 3D globe and street view of a [NetBox Database](https://netbox.dev/). It is possible to use Unreal Engine 4, but this repository has been tested only with Unreal Engine 5.

This plugin was originally created to display the G2 Trace Graph from the [Qualcomm AI Research Department](https://www.qualcomm.com/research/artificial-intelligence/ai-research). However, the main purpose has centered on NetBox functionality. Additionally, the Data Utils Trace Graph will used in the event that the G2 Trace Graph in inaccessible.

Currently the Street View is currently in development and does not have much functionality yet.

Please contact [matthewdzane@gmail.com](matthewdzane@gmail.com) for access to the private repository, which contains the source code.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

This project requires several Unreal Engine 5 and non-Unreal Engine 5 libraries. 

* [Netbox](https://github.com/netbox-community/netbox)
* [G2 Trace Graph](https://www.qualcomm.com/research/artificial-intelligence/ai-research)
* [Reztly](https://github.com/MatthewDZane/Reztly)
* [Cesium For Unreal](https://cesium.com/platform/cesium-for-unreal/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

First, a NetBox instance must be setup and running. We will not go over the NetBox installation process here, but NetBox installation instruction can be found [here](https://docs.netbox.dev/en/stable/). 

Additionally, ensure that you have access to the [Reztly](https://github.com/MatthewDZane/Reztly) repository.

The Cesium For Unreal Plugin can be found [here](https://www.unrealengine.com/marketplace/en-US/product/87b0d05800a545d49bf858ef3458c4f7).

### Installation

_Below are instruction on how to setup NetBox for the Cesium NetBox Visualization plugin._

1. Add a Site, Device, and Device Type entry with the name "TBD".
2. Import the Custom Fields in [netbox_custom fields.csv](https://github.com/MatthewDZane/CesiumNetBoxVisualization/netbox_custom_fields.csv)

_Below are instruction on how to setup the Cesium NetBox Visualization plugin in an Unreal Engine 5 project._

1. Create Unreal Engine 5 project and ensure that there is a "Plugins" folder.
2. Clone this Repository into the "Plugins" folder. If the project is already using Git, the plugin can be added as a submodule.
```
git submodule add https://github.com/MatthewDZane/CesiumNetBoxVisualization Plugins/CesiumNetBoxVisualization
```
4. Clone the [Reztly](https://github.com/MatthewDZane/Reztly) Repository into the "Plugins" folder. 
If the project is already using Git, the plugin can be added as a submodule.
```
git submodule add https://github.com/MatthewDZane/Reztly Plugins/Reztly
```
3. Install the Cesium for Unreal Plugin in the Engine or in the "Plugins" folder.
4. In a file explorer, right click the .uproject file and select the "Generate Visual Studio Project Files" option. 
5. In Visual Studio, build the project.
6. Open the project in Unreal Engine 5 to utilize and develop with the plugin.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

First, there must be a SINGLE BP_NetBox_Visualization_Controller object in the map. This object makes REST API requests to G2, Data Utils, and NetBox and then relays the data to the BP_NetBox_Visualization actors. In fact, the BP_NetBox_Visualization actors will not work unless there is a SINGLE BP_NetBox_Visualization_Controller object in the map. It is also responsible for making remote updates to NetBox. This object can be placed anywhere in the world and does not have a physical model.

Next, any number of BP_NetBox_Visualization actors can be placed in the map. Additionally, new BP_NetBox_Visualization actors can be spawned anytime after gameplay begins. There are 2 types of BP_NetBox_Visualization actors, 1) the BP_NetBox_Visualization actor itself, which is a basic Earth View and 2) a BP_NetBox_Visualization_Cesium actor, which uses the Cesium Earth model. The basic Earth View uses a simple low detail Earth Model, while the Cesium Earth version allows the player to zoom from a Global level view to a Ground level view, with varying levels of detail, depending on the level of zoom.

Although all of the PlayerControllers, Pawns, and Maps can be used as they are in the plugin, it is recommended to create one's own version or use these classes a parents to one's own classes, when developing with the plugin. This allows one to use the original functionality, while overriding other functions that one wishes to modify.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Add Ground Level View
  - [ ] Locations
  - [ ] Racks
  - [ ] Devices
- [ ] Fix BP_NetBox_Visualization Region Displays

See the [open issues](https://github.com/MatthewDZane/CesiumNetBoxVisualization/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Matthew Zane - [@matthewdzane](https://www.linkedin.com/in/matthewdzane/) - MatthewDZane@gmail.com

Project Link: [https://github.com/MatthewDZane/CesiumNetBoxVisualization]https://github.com/MatthewDZane/CesiumNetBoxVisualization)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [NetBox Documentation](https://docs.netbox.dev/en/stable/)
* [NetBox Repository](https://github.com/netbox-community/netbox)
* [Reztly Repository](https://github.com/MatthewDZane/Reztly)
* [Cesium For Unreal](https://cesium.com/platform/cesium-for-unreal/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/MatthewDZane/CesiumNetBoxVisualizationPreview.svg?style=for-the-badge
[contributors-url]: https://github.com/MatthewDZane/CesiumNetBoxVisualizationPreview/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/MatthewDZane/CesiumNetBoxVisualizationPreview.svg?style=for-the-badge
[forks-url]: https://github.com/MatthewDZane/CesiumNetBoxVisualizationPreview/network/members
[stars-shield]: https://img.shields.io/github/stars/MatthewDZane/CesiumNetBoxVisualizationPreview.svg?style=for-the-badge
[stars-url]: https://github.com/MatthewDZane/CesiumNetBoxVisualizationPreview/stargazers
[issues-shield]: https://img.shields.io/github/issues/MatthewDZane/CesiumNetBoxVisualizationPreview.svg?style=for-the-badge
[issues-url]: https://github.com/MatthewDZane/CesiumNetBoxVisualizationPreview/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/matthewdzane
[product-screenshot]: images/screenshot.png
