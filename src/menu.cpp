#include "menu.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <cstdlib>  
#include <cctype>   
using namespace std;

Menu::Menu(ListDoubly<Recipe>& rb) : listRecipeBook(&rb) {
    int opcControl;
    bool foundFilter;

    do {
        cout << "-------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\n\t\t\t\t  RECETARIO DIGITAL\n\n";
        int recipes = 0;
        ListDoubly<Recipe>::Position pos0 = listRecipeBook->getFirstPos();
                        for (int i = 0; pos0 != nullptr; i++) {
                            recipes++;
                            pos0 = listRecipeBook->getNextPos(pos0);
                        }
        if(recipes == 0){
            cout << "Recetario vacio" << endl;
        } else {              
            cout << "Numero de recetas: " << recipes << endl;
        }

        cout <<"\n1. Nueva receta\n" << "2. Eliminar receta\n" << "3. Eliminar toda las recetas\n" << "4. Buscar receta\n" << "5. Ordenar Recetas \n" 
        << "6. Editar lista de ingredientes \n" << "7. Editar porcedimiento de una receta \n" << "8. Mostrar recetas\n" << "9. Guardar en disco\n" << "10. Leer del disco\n" << "11. Salir";
        cout << "\nElija una opcion: ";
        cin >> opcControl;
        cin.ignore();
        switch (opcControl)
        {
            case 1: {
                char opc;
                do {
                    Recipe recipeAux;
                    string data;
                    Name name;
                    int categ, prepTime;
                    cout << "\t\t\t\t\t\t<<<<<Insertar nueva receta>>>>>\n\n";
                    cout << "Nombre de la receta: ";
                    getline(cin, data);
                    recipeAux.setRecipeName(data);

                    cout << "Tiempo de preparacion (en minutos): ";
                    cin >> prepTime;
                    recipeAux.setPreparationTime(prepTime);
                    cin.ignore();

                    cout << "Precedimiento: ";
                    getline(cin, data);
                    recipeAux.setProcedure(data);

                    cout << "Categorias: " << endl;
                    cout << "1. Desayuno\n" << "2. Comida\n" << "3. Cena\n" << "4. Navideno\n";
                    cout << "Elija una categoria: ";
                    cin >> categ;
                    recipeAux.setCategory(categ);
                    cin.ignore();

                    cout << "Apellido del chef(autor): ";
                    getline(cin, data);
                    name.setLast(data);

                    cout << "Nombre del chef(autor): ";
                    getline(cin, data);
                    name.setFirst(data);

                    recipeAux.setChefAuthorName(name);

                    char addIngredients;
                    cout << "\n<Ingredientes>\n";
                    do {
                        Ingredients ingredientAux;
                        string ingredient;
                        string amount;

                        cout << "\nNombre del ingrediente: ";
                        getline(cin, ingredient);
                        ingredientAux.setIngredients(ingredient);

                        cout << "Cantidad: ";
                        getline(cin, amount);
                        ingredientAux.setAmount(amount);

                        // Acceder a la lista de ingredientes directamente
                        recipeAux.getIngredientList().insertDataSorted(ingredientAux, Ingredients::compareIngredients);

                        cout << "Desea agregar otro ingrediente? (S/N): ";
                        cin >> addIngredients;
                        cin.ignore();

                        addIngredients = toupper(addIngredients);
                    } while (addIngredients == 'S');


                    try {
                        listRecipeBook->insertData(listRecipeBook->getLastPos(), recipeAux);
                    } catch(const ListDoubly<Recipe>::Exception& ex) {
                        cout << "Hubo un error: " << ex.what() << endl;
                        break;
                    }
                    cout << "\nReceta anadida exitosamente!!!\n" << endl;
                    cout << "Desea insertar otra receta? (S/N): ";
                    cin >> opc;
                    cout << endl;
                    cin.ignore();

                    opc = toupper(opc);
                    
                }while(opc =='S');  
                system("cls");
            }
                break; 
            case 2: {
                if (listRecipeBook->isEmpty()) {
                    cout << "\nEl recetario esta vacio, no hay recetas para eliminar\n\n";
                    break;
                }
            
                string recipeName;
                Recipe recipeAux;
                cout << "\t\t\t\t\t\t<<<<Eliminar receta por nombre>>>>\n\n";
                cout << "Ingrese el nombre de la receta que desea eliminar: ";
                getline(cin, recipeName);
            
                recipeAux.setRecipeName(recipeName);
            
                //Busca la receta con el nombre especiicado
                ListDoubly<Recipe>::Position pos = listRecipeBook->findDataByRecipeName(recipeAux, Recipe::compareNameRecipe);           
                if (pos == nullptr) {
                    system("cls");
                    cout << "\nNo se encontro una receta con el nombre '" << recipeName << "'.\n\n";
                } else {
                    cout << "\nReceta encontrada!!!\n";
                    cout << listRecipeBook->retrieve(pos).toString() << "\n";
            
                    char confirm;
                    cout << "Esta seguro de que desea eliminar esta receta? (S/N): ";
                    cin >> confirm;
                    cin.ignore();
            
                    if (toupper(confirm) == 'S') {
                        try {
                            listRecipeBook->deleteData(pos);
                            system("cls");
                            cout << "\nReceta eliminada exitosamente!!!\n\n";
                        } catch (const ListDoubly<Recipe>::Exception& ex) {
                            cout << "Error al eliminar la receta: " << ex.what() << "\n\n";
                        }
                    } else {
                        system("cls");
                        cout << "\nEliminacion cancelada!!!\n\n";
                    }
                }
                
            }
                break;
            case 3:{
                char opc;
                if(listRecipeBook->getLastPos() != nullptr){
                    cout <<"\nDesea eliminar todas las recetas?" << endl;
                    cout << "(S/N): ";
                    cin >> opc;

                    opc = toupper(opc);

                    if(opc == 'S'){
                        listRecipeBook->deleteAll();
                        system("cls");
                        cout << "\nRecetas eliminadas!!!\n\n";
                    } else if (opc == 'N'){
                        system("cls");
                        cout << "\nLas recetas no se eliminaron!!!\n\n";
                    } else {
                        system("cls");
                        cout << "\nOpcion invalida!!!\n\n";
                    }
                }else {
                    cout << "\nEl recetario esta vacio, no hay recetas para eliminar\n\n";
                }
            }   
                break;
            case 4:{
                //Verifca si hay recetas
                if (listRecipeBook->isEmpty()) {
                    cout << "\nEl recetario esta vacio, no hay recetas para buscar\n\n";
                    break;
                }
                int criterion;
                Recipe search;
                string data;
                int categ;
                cout << "\t\t\t\t\t\t\t<<<<<Buscar receta>>>>>\n\n";

                cout << "\nSeleccione el criterio de busqueda:\n";
                cout << "1. Por nombre de la receta\n";
                cout << "2. Por la categoria de la receta\n";
                cout << "Digite una opcion: ";
                cin >> criterion;
                cin.ignore();
            
                if (criterion == 1) { 
                    cout << "\nIngrese el nombre de la receta: ";
                    getline(cin, data);

                    search.setRecipeName(data);   

                    ListDoubly<Recipe>::Position pos = listRecipeBook->findDataByRecipeName(search, Recipe::compareNameRecipe);           
                    if (pos == nullptr) {
                        system("cls");
                        cout << "\nReceta no encontrada\n\n";
                    } else {
                        system("cls");
                        cout << "\nReceta de " << data << " encontrada!!!" << endl;
                        cout << listRecipeBook->retrieve(pos).toString() << "\n\n";
                    }
                } else if(criterion == 2) {
                    cout << "\nIngrese la categoria de la receta: ";
                    cout << "\n1. Desayuno\n" << "2. Comida\n" << "3. Cena\n" << "4. Navideno\n";
                    cout << "Digite una categoria: ";
                    cin >> categ;
                    if(categ <= 4 || categ >= 1){ //Verifica si se ingreso una categoria valida
                        search.setCategory(categ);

                        ListDoubly<Recipe>::Position pos = listRecipeBook->findDataByCategory(search, Recipe::compareCategory);           
                        if (pos == nullptr) {
                            system("cls");
                            cout << "\nReceta no encontrada\n\n";
                        } else {
                            system("cls");
                            cout << "\nReceta de la categoria " << search.getCategory() << " encontrada!!!" << endl;
                            cout << listRecipeBook->retrieve(pos).toString() << "\n\n";
                        }     
                    } else {
                        cout << "Categoria invalida!!!\n\n";
                    }           
                } else {
                    cout << "\nCriterio invalido!!!\n\n";
                    break;
                }
            }   
                break;
            case 5:{
                //Verifca si hay recetas
                if (listRecipeBook->isEmpty()) {
                    cout << "\nEl recetario esta vacio, no hay recetas para ordenar\n\n";
                    break;
                }
                cout << "\t\t\t\t\t\t\t<<<<<Ordenar recetas>>>>>\n\n";
                int criterion;
                string data;
                cout << "\nSeleccione el criterio de ordenamiento:\n";
                cout << "1. Por nombre de receta\n";
                cout << "2. Por tiempo de preparacion\n";
                cout << "Digite una opcion: ";
                cin >> criterion;
                cin.ignore();

                
                if (criterion == 1) { 
                    if(listRecipeBook->isSorted(Recipe::compareNameRecipe)){ //Verifica si ya estan ordenadas por nombre
                        system("cls");
                        cout << "La lista ya esta ordenanda!!!\n\n";
                        break;
                    }
                listRecipeBook->sortDataQuick(Recipe::compareNameRecipe); //Ordena por medio de el nombre
                system("cls");
                cout << "Lista ordenanda con exito!!!\n\n";
                } else if (criterion == 2) { 
                    if(listRecipeBook->isSorted(Recipe::comparePrepTime)){ //Verifica si ya estan ordenadas por tiempo de prep
                        system("cls");
                        cout << "La lista ya esta ordenanda!!!\n\n";
                        break;
                    }
                listRecipeBook->sortDataQuick(Recipe::comparePrepTime); //Ordena por medio de el tiempo de prep
                system("cls");
                cout << "Lista ordenanda con exito!!!\n\n";
                } else {
                    system("cls");
                    cout << "\nCriterio invalido!!!\n\n";
                    break;
                } 
                
            }
                break;
            case 6:{      
                if (listRecipeBook->isEmpty()) { // Verifica si hay recetas
                    cout << "\nEl recetario esta vacio, no hay recetas para editar.\n\n";
                    break;
                }

                string recipeName;
                Recipe recipeAux;
                cout << "\t\t\t\t\t\t<<<<<Editar ingredientes de una receta>>>>>\n\n";
                cout << "Ingrese el nombre de la receta que desea editar: ";
                getline(cin, recipeName);

                recipeAux.setRecipeName(recipeName);

                // Busca la receta con el nombre especificado
               ListDoubly<Recipe>::Position pos = listRecipeBook->findDataByRecipeName(recipeAux, Recipe::compareNameRecipe);           

                if (pos == nullptr) {
                    system("cls");
                    cout << "\nNo se encontro una receta con el nombre '" << recipeName << "'!!!!\n\n";
                } else {
                    Recipe& recipeToEdit = listRecipeBook->retrieve(pos); // Obtener la referencia a la receta

                    int ingredientOption;
                    do {
                        cout << "\n\t\t\t\t\t\t\tMenu de edicion de ingredientes\n\n";
                        cout << "1. Agregar un ingrediente\n";
                        cout << "2. Eliminar un ingrediente\n";
                        cout << "3. Eliminar todos los ingredientes\n";
                        cout << "4. Modificar la cantidad de un ingrediente\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Digite una opcion: ";
                        cin >> ingredientOption;
                        cin.ignore();
                        switch (ingredientOption) {
                            case 1: { // Agregar un ingrediente
                                Ingredients ingredientAux;
                                string ingredient, amount;

                                cout << "\nNombre del ingrediente: ";
                                getline(cin, ingredient);
                                ingredientAux.setIngredients(ingredient);

                                cout << "Cantidad: ";
                                getline(cin, amount);
                                ingredientAux.setAmount(amount);
                                

                                // Insertar el ingrediente en la lista de ingredientes de la receta
                                recipeToEdit.getIngredientList().insertDataSorted(ingredientAux, Ingredients::compareIngredients);

                                cout << "\nIngrediente agregado exitosamente!!!\n\n";
                            }
                                break;
                            case 2: { // Eliminar un ingrediente
                                if (recipeToEdit.getIngredientList().isEmpty()) {
                                    cout << "\nLa receta no tiene ingredientes para eliminar.\n\n";
                                    break;
                                }

                                string ingredientToDelete;
                                cout << "\nIngrese el nombre del ingrediente que desea eliminar: ";
                                getline(cin, ingredientToDelete);

                                bool found = false;
                                typename  ListSimple<Ingredients>::Position ingPos = recipeToEdit.getIngredientList().getFirstPos();
                                for (int i = 0; ingPos != nullptr; i++) {
                                    Ingredients currentIngredient = recipeToEdit.getIngredientList().retrieve(ingPos);
                                    if (currentIngredient.getIngredients() == ingredientToDelete) {
                                        recipeToEdit.getIngredientList().deleteData(ingPos);
                                        found = true;
                                        cout << "\nIngrediente eliminado exitosamente!!!\n\n";
                                        break;
                                    }
                                    ingPos = recipeToEdit.getIngredientList().getNextPos(ingPos);
                                }

                                if (!found) {
                                    cout << "\nNo se encontro el ingrediente '" << ingredientToDelete << "' en la receta!!!\n\n";
                                }
                            }
                                break;
                            case 3: { // Eliminar todos los ingredientes
                                if (recipeToEdit.getIngredientList().isEmpty()) {
                                    cout << "\nLa receta no tiene ingredientes para eliminar!!!\n\n";
                                    break;
                                }

                                char confirm;
                                cout << "\nEstas seguro de que desea eliminar todos los ingredientes de la receta? (S/N): ";
                                cin >> confirm;
                                cin.ignore();

                                if (toupper(confirm) == 'S') {
                                    recipeToEdit.getIngredientList().deleteAll();
                                    cout << "\nTodos los ingredientes han sido eliminados exitosamente!!!\n\n";
                                } else {
                                    cout << "\nEliminacion cancelada!!!\n\n";
                                }
                                break;
                            }
                            case 4: { // Modificar la cantidad de un ingrediente
                                if (recipeToEdit.getIngredientList().isEmpty()) {
                                    cout << "\nLa receta no tiene ingredientes para modificar.\n\n";
                                    break;
                                }

                                string ingredientToModify;
                                cout << "\nIngrese el nombre del ingrediente cuya cantidad desea modificar: ";
                                getline(cin, ingredientToModify);

                                bool found = false;
                                typename  ListSimple<Ingredients>::Position ingPos2 = recipeToEdit.getIngredientList().getFirstPos();
                                for (int i = 0; ingPos2 != nullptr; i++) {
                                    Ingredients& currentIngredient = recipeToEdit.getIngredientList().retrieve(ingPos2);
                                    if (currentIngredient.getIngredients() == ingredientToModify) {
                                        string newAmount;
                                        cout << "Ingrese la nueva cantidad: ";
                                        getline(cin, newAmount);
                                        currentIngredient.setAmount(newAmount);
                                        found = true;
                                        cout << "\nCantidad del ingrediente modificada exitosamente!!!\n\n";
                                        break;
                                    }
                                        ingPos2 = recipeToEdit.getIngredientList().getNextPos(ingPos2);
                                }

                                if (!found) {
                                    cout << "\nNo se encontro el ingrediente '" << ingredientToModify << "' en la receta!!!\n\n";
                                }
                                break;
                            }
                            case 5: { // Volver al menú principal
                                system("cls");
                                cout << "\nVolviendo al menu principal...\n\n";
                                break;
                            }
                            default: {
                                cout << "\nOpcion invalida. Intente de nuevo.\n\n";
                                break;
                            }
                        }
                    } while (ingredientOption != 5);
                }
            }
                break;            
            case 7:{
                //Veriica si hay recetas
                if (listRecipeBook->isEmpty()) {
                    cout << "\nEl recetario esta vacio!!!\n\n";
                    break;
                }
            
                string recipeName;
                Recipe recipeAux;
                cout << "\t\t\t\t\t\t<<<<<Editar procedimiento de una receta>>>>>\n\n";
                cout << "Ingrese el nombre de la receta que desea editar: ";
                getline(cin, recipeName);
            
                recipeAux.setRecipeName(recipeName);
            
                //Busca la receta cn el nombre especificado para editarla
                ListDoubly<Recipe>::Position pos = listRecipeBook->findDataByRecipeName(recipeAux, Recipe::compareNameRecipe);           
            
                if (pos == nullptr) {
                    system("cls");
                    cout << "\nNo se encontro una receta con el nombre '" << recipeName << "'.\n\n";
                } else {
                    string newProcedure;          
                    cout << "\nReceta encontrada!!!\n";
                    cout << listRecipeBook->retrieve(pos).toString() << "\n\n";

                    ListDoubly<Recipe>::Position prevPos = pos->getPrev();

                    Recipe recipeToEdit = listRecipeBook->retrieve(pos);

                    cout << "Ingrese el nuevo procedimiento: ";
                    getline(cin, newProcedure);

                    // Modificamos la copia
                    recipeToEdit.setProcedure(newProcedure);

                    // Eliminamos la receta original y reinsertamos la modificada
                    listRecipeBook->deleteData(pos);
                    listRecipeBook->insertData(prevPos, recipeToEdit);  // Insertamos en la misma posición

                    system("cls");
                    cout << "\nProcedimiento actualizado exitosamente!!!\n\n";
                }
            }
                break;
            case 8:{
                //Verifca si hay recetas
                if (listRecipeBook->isEmpty()) {
                    cout << "\nEl recetario esta vacio, no hay recetas para filtrar\n\n";
                    break;
                }
                cout << "\t\t\t\t\t\t<<<<<Filtrar rectas>>>>>\n\n";
                int filter;
                cout << "Seleccione una opcion:\n";
                cout << "1. Mostrar todas las recetas\n";
                cout << "2. Filtrar por categoria\n";
                cout << "Digite una opcion: ";
                cin >> filter;
                cin.ignore();

                if (filter == 1) {
                    system("cls");
                    cout << "\nFiltro aplicado. Se mostraran todas las recetas.\n\n";
                    filterCategory = "";
                    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
                    cout << "\t\t\t\t Todas las recetas registradas\n";

                    ListDoubly<Recipe>::Position pos = listRecipeBook->getFirstPos();
                    for (int i = 0; pos != nullptr; i++) {
                        Recipe recipeAux = listRecipeBook->retrieve(pos);
                        if (filterCategory.empty() || recipeAux.getCategory() == filterCategory || foundFilter == false) {
                            cout << recipeAux.toString();
                        }
                        pos = listRecipeBook->getNextPos(pos);
                    }
                    
                } else if (filter == 2) {
                    int category;
                    cout << "\nSeleccione la categoria:\n";
                    cout << "1. Desayuno\n";
                    cout << "2. Comida\n";
                    cout << "3. Cena\n";
                    cout << "4. Navideno\n";
                    cout << "Digite una opcion: ";
                    cin >> category;
                    cin.ignore();

                    if (category >= 1 && category <= 4) {
                        switch (category) {
                            case 1: filterCategory = "Desayuno"; break;
                            case 2: filterCategory = "Comida"; break;
                            case 3: filterCategory = "Cena"; break;
                            case 4: filterCategory = "Navideno"; break;
                        }

                        //Verificar si hay recetas con la categoria elgida
                        foundFilter = false;
                        ListDoubly<Recipe>::Position pos = listRecipeBook->getFirstPos();
                        for (int i = 0; pos != nullptr; i++) {
                            Recipe recipeAux = listRecipeBook->retrieve(pos);
                            if (recipeAux.getCategory() == filterCategory) {
                                foundFilter = true;
                            }
                            pos = listRecipeBook->getNextPos(pos);
                        }
            
                        if (!foundFilter) {
                            system("cls");
                            cout << "\nNo se encontraron recetas de la categoria '" << filterCategory << "'!!!\n\n";
                        } else {
                            system("cls");
                            cout << "\n\nFiltro aplicado. Se mostraran solo las recetas de la categoria '" << filterCategory << "'!!!\n\n";
                            cout << "-------------------------------------------------------------------------------------------------------------" << endl;
                            cout << "\t\t\t\t Recetas registradas filtradas\n";

                            ListDoubly<Recipe>::Position pos = listRecipeBook->getFirstPos();
                            for (int i = 0; pos != nullptr; i++) {
                                Recipe recipeAux = listRecipeBook->retrieve(pos);
                                if (filterCategory.empty() || recipeAux.getCategory() == filterCategory || foundFilter == false) {
                                    cout << recipeAux.toString();
                                }
                                pos = listRecipeBook->getNextPos(pos);
                            }                                          
                        }
                    } else {
                        system("cls");
                        cout << "\nCategoria invalida. Filtro no aplicado.\n\n";
                    }
                } else {
                    system("cls");
                    cout << "\nOpcion invalida. Filtro no aplicado.\n\n";
                }

            }
                break;
            case 9:{
                try {
                    listRecipeBook->writeToDisk("recetas.txt");
                    cout << "\nRecetas guardadas exitosamente!\n\n";
                } catch(const ListDoubly<Recipe>::Exception& ex) {
                    cout << "\nError al guardar: " << ex.what() << "\n\n";
                }
            }
                break;
            case 10:{
                try {
                    listRecipeBook->readFromDisk("recetas.txt");
                    cout << "\nRecetas cargadas exitosamente!\n\n";
                } catch(const ListDoubly<Recipe>::Exception& ex) {
                    cout << "\nError al cargar: " << ex.what() << "\n\n";
                }
            }
                break;
            case 11:{
                cout << "\nSaliendo del programa...";
            }
                break;
            default: {
                cout << "\nOpcion invalida\n\n";
            }
                break;
        }
    }while (opcControl != 11);  

    cout << "\nPresione [ENTER] para continuar...";
    getchar();
}            