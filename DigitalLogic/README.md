# Digital Logic

Circuits built with [Digital](https://github.com/hneemann/Digital) (`.dig` files).

| Folder | Contents |
|---|---|
| [Labs](Labs) | Lab02–Lab05, one folder per problem (`Template.dig` + problem PDF) |
| [Exams](Exams) | Past exams 66–68: `Q*_Template.dig.xml` + `truth.csv` |
| [Practice](Practice) | Extra practice circuits |
| [Tools/diglo_helper](Tools/diglo_helper) | `.pla` → espresso → `.dig` generator that matches the official Template ([guide](Tools/diglo_helper/README.md)) |
| `Digital/` | The Digital simulator itself (not in git). Run `Digital/Digital.sh` or `java -jar Digital/Digital.jar` |

> `Digital/` must stay at this level: `pla2dig.py` finds `Digital/Digital.jar` by walking up from the Template file.
