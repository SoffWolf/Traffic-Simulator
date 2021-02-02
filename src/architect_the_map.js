//var XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;
const fs = require('fs') 

function add_road(text, type, num, id, name){
    if (type == "vertical"){
        text += "<way id=\"" + id + "\" name=\"" + name + "\">\n"
        for (i = 1; i <= 100; i++){
            text += "\t" + "<nd ref=\"" + String((i-1)*100+num) + "\" lon=\"" +
            String(i) + "\" lat=\"" + String(num) + "\"></nd>"+ '\n'
        }
        text += "</way>\n"
    }
    else if (type == "horizontal"){
        text += "<way id=\"" + id + "\" name=\"" + name + "\">\n"
        for (i = 1; i <= 100; i++){
            text += "\t" + "<nd ref=\"" + String((num-1)*100+i) + "\" lon=\"" +
            String(num) + "\" lat=\"" + String(i) + "\"></nd>"+ '\n'
        }
        text += "</way>\n"
    }
    else{
        print("Error.");
    }
    return text;
}

/////////////////////////////////
function add_intersection(text, lon, lat, id, light, h_ref, h_name, v_ref, v_name){
    text += "<intersection id=\"" + id + "\" lon=\"" +
    String(lon) + "\" lat=\"" + String(lat)+ "\" traffic_light=\"" + light + "\">" + '\n';

    text += "\t" + "<two_road ref=\"" + String(h_ref) + "\" name=\"" +
            h_name + "\"></two_road>"+ '\n';

    text += "\t" + "<two_road ref=\"" + String(v_ref) + "\" name=\"" +
    v_name + "\"></two_road>"+ '\n';

    text += "</intersection>\n"
    return text;
}


function add_building(text, start_lon, start_lat, end_lon, end_lat, id, name, type, entrance_lon, entrance_lat){
    text += "<building id=\"" + id + "\" name=\"" +
    name +  "\" type=\"" + type + "\" entrance_lon=\"" + entrance_lon + "\" entrance_lat=\"" + entrance_lat + "\">" + '\n';
    for (i = start_lat; i <= end_lat; i++){
        for (j = start_lon; j <= end_lon; j++){
            text += "\t<nd id=\"" + String((i-1)*100+j) + "\" lon=\"" +
            String(i) + "\" lat=\"" + String(j) + "\"></nd>"+ '\n';
        }
    }
    text += "</building>\n";
    return text;
}


//main
var txt = "";
//create 10000 nodes
// for (i = 1; i <= 100; i++){
//     for (j = 1; j <= 100; j++){
//         txt += "<node id=\"" + String((i-1)*100+j) + "\" lon=\"" +
//         String(i) + "\" lat=\"" + String(j) + "\">"+ '\n'
        
//     }}


txt += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
txt += "<root>\n"
//add building first, then road, then intersection
txt += "<buildings>"
txt = add_building(txt, 53, 53, 60, 60, 77777, "Aalto University", "Education", 50, 57);
txt = add_building(txt, 40, 40, 47, 47, 88888, "MIT University", "Education", 50, 43);
txt = add_building(txt, 40, 53, 47, 60, 99999, "Harvard University", "Education", 43, 50);
txt = add_building(txt, 53, 40, 60, 47, 66666, "CalTech University", "Education", 57, 50);
txt += "</buildings>"

txt += "<ways>"
txt = add_road(txt, "vertical", 50, 9999, "King Street");
txt = add_road(txt, "horizontal", 50, 9998, "Queen Street");
txt += "</ways>"

txt += "<intersections>"
txt = add_intersection(txt, 50, 50, 123456, true, 9998, "King Street", 9999, "Queen Street");
txt += "</intersections>"

txt += "</root>"





fs.writeFile('the_map.xml', txt, (err) => { 
    
    // In case of a error throw err. 
    if (err) throw err; 
})




// function myFunction() {
//     var i, j, newElement, xmlDoc;
//     var xmlDoc = document.implementation.createDocument("", "", null);
//     for (i = 1; i < 100; i++){
//         for (j = 1; j < 100; j++){
//             newElement = xmlDoc.createElement("node");
//             newElement.setAttribute("lon", i);
//             newElement.setAttribute("lat", j);
//             newElement.setAttribute("id", (i-1)*100+j);
//             xmlDoc.appendChild(newElement);
            
//         }
//     }
//     fs.writeFile('Output.txt', xmlDoc, (err) => { 
      
//         // In case of a error throw err. 
//         if (err) throw err; 
//     }) 
//     return 0;
// }
// myFunction();
