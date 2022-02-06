// Used to make sure the scripts are being accessed
function hello_world() {
	alert("Hello, World!")
}

// Toggles calorie textbar
function toggle_cal_max() {
	var element = document.getElementById("cal_max");
	var elementLabel = document.getElementById("cal_max_label");
	if (element.style.visibility === "hidden")	{
		element.style.visibility = "visible";
		elementLabel.style.visibility = "visible";
	}
	else {
		element.style.visibility = "hidden";
		elementLabel.style.visibility = "hidden";
		element.value = "";
	}
}

// SHOULD be capable of getting input for displaying on html page when called
function display_recipe(image_url, description, prep_time, cook_time) {
	let image = document.createElement("img");
	image.src = image_url;
	image.width = "500";
	image.className = "display_image";

	let text = document.createElement("p");
	text.innerHTML = description;
	text.className = "display_text";

	let prep = document.createElement("p");
	let prep_time_display = "Prep Time: " + prep_time + " minutes";
	prep.innerHTML = prep_time_display;
	prep.className = "display_text";

	let cook = document.createElement("p");
	let cook_time_display = "Cook Time: " + cook_time + " minutes";
	cook.innerHTML = cook_time_display;
	cook.className = "display_text";

	let main = document.getElementById("home");
	main.appendChild(image);
	main.appendChild(text);
	main.appendChild(document.createElement("br"));
	main.appendChild(prep);
	main.appendChild(cook);

}

/*
This probably doesn't work and it's also unnecessary.
In other words, I'm stupid for wasting time on this.

function set_cookies() {
	let cookie_string = "";
	let ids = ["vegan","vegetarian","gluten_free","dairy_free",
			"kosher","no_nuts","no_shellfish","no_eggs","no_fish",
			"no_soy","no_sesame","skill_level","cal_max"];

	for(id in ids) {
		let temp_element = document.getElementById(ids[id]);
		if (temp_element.value === "")
			continue;
		cookie_string = cookie_string.concat(ids[id] + "=" + temp_element.value + ";");
		alert(cookie_string);
	}

	//document.cookie = cookie_string;
}
*/